// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeGenerator.h"
#include "MazeFirstGameModeBase.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

struct FCell
{
    uint8 X;
    uint8 Y;
    uint32 Distance = 0;
    bool bHasLeft = true;
    bool bHasBottom = true;
    bool bIsVisited = false;
};

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SceneComponent->SetMobility(EComponentMobility::Static);
    SetRootComponent(SceneComponent);
    WallComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallComponent"));
    WallComponent->SetupAttachment(RootComponent);
    FloorComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorComponent"));
    FloorComponent->SetupAttachment(RootComponent);
    ColumnComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ColumnComponent"));
    ColumnComponent->SetupAttachment(RootComponent);
    StartComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartComponent"));
    StartComponent->SetupAttachment(RootComponent);
    StartComponent->SetRelativeLocation(FVector(-CellSize, 0.0f, 0.0f));
    EndComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndComponent"));
    EndComponent->SetupAttachment(RootComponent);
    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SplineComponent->SetupAttachment(RootComponent);
    Path = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PathEffect"));
    Path->SetupAttachment(RootComponent);
}

void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(World)))
    {
        GameMode->ShowHelpPath.AddUObject(this, &AMazeGenerator::ShowPath);
        GameMode->GenerateNewMaze.AddUObject(this, &AMazeGenerator::GenerateMaze);
        GameMode->RestartMaze.AddUObject(this, &AMazeGenerator::HidePath);
    }
    checkf(WallComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(FloorComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(ColumnComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(StartComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(EndComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    GenerateMaze();
    check(Path);
    Path->SetActorParameter(SplineName, this);
    //Path->SetIntParameter("spawn_rate", 10);
    //Path->SetIntParameter("lifetime", 50);
}

void AMazeGenerator::GenerateMaze()
{
    ResetMaze();
    FCell** Cells = new FCell*[Width];
    for (uint8 i = 0; i < Width; i++)
    {
        Cells[i] = new FCell[Height];
        for (uint8 j = 0; j < Height; j++)
        {
            Cells[i][j] = {i, j};
        }
    }
    RemoveWallsWithBackTracker(Cells);
    PlaceExit(Cells);
    BuildGeometry(Cells);
    FindPath(Cells);
    for (uint8 i = 0; i < Width; i++)
    {
        delete [] Cells[i];
    }
    delete [] Cells;
}

void AMazeGenerator::RemoveWallsWithBackTracker(FCell** Cells)
{
    FCell* Current = &Cells[0][0];
    Current->bIsVisited = true;
    TArray<FCell*> Stack;
    do
    {
        TArray<FCell*> UnvisitedNeighbours;
        const uint8 X = Current->X;
        const uint8 Y = Current->Y;
        if (X > 0 && !Cells[X - 1][Y].bIsVisited)
        {
            UnvisitedNeighbours.Add(&Cells[X - 1][Y]);
        }
        if (Y > 0 && !Cells[X][Y - 1].bIsVisited)
        {
            UnvisitedNeighbours.Add(&Cells[X][Y - 1]);
        }
        if (X < Width - 1 && !Cells[X + 1][Y].bIsVisited)
        {
            UnvisitedNeighbours.Add(&Cells[X + 1][Y]);
        }
        if (Y < Height - 1 && !Cells[X][Y + 1].bIsVisited)
        {
            UnvisitedNeighbours.Add(&Cells[X][Y + 1]);
        }
        if (UnvisitedNeighbours.Num() > 0)
        {
            FCell* Chosen = UnvisitedNeighbours[FMath::RandRange(0, UnvisitedNeighbours.Num() - 1)];
            RemoveWall(Current, Chosen);
            Chosen->bIsVisited = true;
            Stack.Push(Chosen);
            Chosen->Distance = Current->Distance + 1;
            Current = Chosen;
        }
        else
        {
            Current = Stack.Pop();
        }
    } while (Stack.Num() > 0);
}

void AMazeGenerator::RemoveWall(FCell* A, FCell* B)
{
    if (A->X == B->X)
    {
        if (A->Y > B->Y)
        {
            A->bHasBottom = false;
        }
        else
        {
            B->bHasBottom = false;
        }
    }
    else
    {
        if (A->X > B->X)
        {
            A->bHasLeft = false;
        }
        else
        {
            B->bHasLeft = false;
        }
    }
}

void AMazeGenerator::PlaceExit(FCell** Cells)
{
    Cells[0][0].bHasBottom = false; //open start
    FCell* Furthest = &Cells[0][0];
    for (uint8 i = 0; i < Width; i++)
    {
        if (Cells[i][Height - 1].Distance > Furthest->Distance)
        {
            Furthest = &Cells[i][Height - 1];
        }
        if (Cells[i][0].Distance > Furthest->Distance)
        {
            Furthest = &Cells[i][0];
        }
    }
    for (uint8 j = 0; j < Height; j++)
    {
        if (Cells[Width - 1][j].Distance > Furthest->Distance)
        {
            Furthest = &Cells[Width - 1][j];
        }
        if (Cells[0][j].Distance > Furthest->Distance)
        {
            Furthest = &Cells[0][j];
        }
    }
    End = FIntVector(Furthest->X, Furthest->Y, 0);
    int8 X = 0;
    int8 Y = 0;
    int8 R = 0;
    if (Furthest->X == 0)
    {
        Furthest->bHasLeft = false;
        X = Furthest->X - 1;
        Y = Furthest->Y;
        R = 0;
    }
    else if (Furthest->Y == 0)
    {
        Furthest->bHasBottom = false;
        X = Furthest->X;
        Y = Furthest->Y - 1;
        //R = 1;
    }
    else if (Furthest->X == Width - 1)
    {
        X = Furthest->X + 1;
        Y = Furthest->Y;
        //R = 2;
    }
    else if (Furthest->Y == Height - 1)
    {
        X = Furthest->X;
        Y = Furthest->Y + 1;
        //R = 3;
    }
    EndComponent->SetRelativeLocation(FVector(CellSize * Y, CellSize * X, 0.0f));
    EndComponent->SetRelativeRotation(FRotator(0.0f, 90.0f * R, 0.0f));
    Exit = FIntVector(X, Y, 0);
}

void AMazeGenerator::BuildGeometry(FCell** Cells)
{
    for (uint8 i = 0; i < Width; i++)
    {
        for (uint8 j = 0; j < Height; j++)
        {
            PlaceColumn(j, i);
            PlaceFloor(j, i);
            if (Cells[i][j].bHasLeft)
            {
                PlaceWall(j, i, -90.0f);
            }
            if (Cells[i][j].bHasBottom)
            {
                PlaceWall(j, i, 0.0f);
            }
        }
    }
    for (uint8 i = 0; i < Width; i++)
    {
        if (i != Exit.X || Exit.Y != Height)
        {
            PlaceWall(Height, i, 0.0f);
        }
        PlaceColumn(Height, i);
    }
    for (uint8 j = 0; j < Height; j++)
    {
        if (j != Exit.Y || Exit.X != Width)
        {
            PlaceWall(j, Width, -90.0f);
        }
        PlaceColumn(j, Width);
    }
    PlaceColumn(Height, Width);
}

void AMazeGenerator::PlaceColumn(const float X, const float Y)
{
    ColumnComponent->AddInstance(FTransform(FVector(CellSize * X, CellSize * Y, 5.0f)));
}

void AMazeGenerator::PlaceFloor(const float X, const float Y)
{
    FloorComponent->AddInstance(FTransform(FVector(CellSize * X, CellSize * Y, 0.0f)));
}

void AMazeGenerator::AddPoint(const uint8 X, const uint8 Y)
{
    const auto Position = FVector((Y + 0.5f) * CellSize, (X + 0.5f) * CellSize, 0.0f);
    SplineComponent->AddSplinePoint(Position, ESplineCoordinateSpace::Local, true);
}

void AMazeGenerator::PlaceWall(const float X, const float Y, const float R)
{
    WallComponent->AddInstance(FTransform(FRotator(0.0f, R, 0.0f), FVector(CellSize * X, CellSize * Y, 5.0f)));
}

void AMazeGenerator::FindPath(FCell** Cells)
{
    FIntVector Current = End;
    AddPoint(Current.X, Current.Y);
    while (!Current.IsZero())
    {
        const auto CurrentCell = Cells[Current.X][Current.Y];
        const auto Distance = CurrentCell.Distance - 1;
        if (Current.X > 0 && !CurrentCell.bHasLeft && Cells[Current.X - 1][Current.Y].Distance == Distance)
        {
            Current.X--;
        }
        else if (Current.Y > 0 && !CurrentCell.bHasBottom && Cells[Current.X][Current.Y - 1].Distance == Distance)
        {
            Current.Y--;
        }
        else if (Current.X < Width - 1 && !Cells[Current.X + 1][Current.Y].bHasLeft && Cells[Current.X + 1][Current.Y].Distance == Distance)
        {
            Current.X++;
        }
        else if (Current.Y < Height - 1 && !Cells[Current.X][Current.Y + 1].bHasBottom && Cells[Current.X][Current.Y + 1].Distance ==
                 Distance)
        {
            Current.Y++;
        }
        else
        {
            break;
        }
        AddPoint(Current.X, Current.Y);
    }
}

void AMazeGenerator::SetShowPath(bool bShow)
{
    Path->SetVisibility(bShow, true);
    Path->SetPaused(!bShow);
}

void AMazeGenerator::ResetMaze()
{
    HidePath();
    WallComponent->ClearInstances();
    FloorComponent->ClearInstances();
    ColumnComponent->ClearInstances();
    SplineComponent->ClearSplinePoints();
}

void AMazeGenerator::ShowPath()
{
    const bool bShow = !Path->IsVisible();
    SetShowPath(bShow);
}

void AMazeGenerator::HidePath()
{
    SetShowPath(false);
}
