// Copyright Alexey Morozov. All Rights Reserved.

#include "GeometryComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Cell.h"

UGeometryComponent::UGeometryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    WallComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallComponent"));
    WallComponent->SetupAttachment(this);
    FloorComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorComponent"));
    FloorComponent->SetupAttachment(this);
    ColumnComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ColumnComponent"));
    ColumnComponent->SetupAttachment(this);
    StartComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartComponent"));
    StartComponent->SetupAttachment(this);
    StartComponent->SetRelativeLocation(FVector(-CellSize, 0.0f, 0.0f));
    EndComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndComponent"));
    EndComponent->SetupAttachment(this);
}

float UGeometryComponent::GetCellSize() const
{
    return CellSize;
}

void UGeometryComponent::Reset()
{
    WallComponent->ClearInstances();
    FloorComponent->ClearInstances();
    ColumnComponent->ClearInstances();
    EndComponent->SetRelativeLocation(FVector::Zero());
}

void UGeometryComponent::Build(const TArray<TArray<FCell>> &Cells, const FIntVector &End)
{
    const auto Exit = PlaceExit(End, Cells[0].Num(), Cells.Num());
    for (const auto &CellA: Cells)
    {
        for (const auto &Cell: CellA)
        {
            PlaceColumn(Cell.X, Cell.Y);
            PlaceFloor(Cell.X, Cell.Y);
            if (Cell.bHasLeft)
            {
                PlaceWall(Cell.X, Cell.Y, -90.0f);
            }
            if (Cell.bHasBottom)
            {
                PlaceWall(Cell.X, Cell.Y, 0.0f);
            }
        }
    }
    const int Width = Cells[0].Num();
    const int Height = Cells.Num();
    for (uint8 i = 0; i < Width; i++)
    {
        PlaceColumn(Height, i);
        if (Height != Exit.X || Exit.Y != i)
        {
            PlaceWall(Height, i, 0.0f);
        }
    }
    for (uint8 i = 0; i < Height; i++)
    {
        PlaceColumn(i, Width);
        if (Width != Exit.Y || Exit.X != i)
        {
            PlaceWall(i, Width, -90.0f);
        }
    }
    PlaceColumn(Height, Width);
}

void UGeometryComponent::BeginPlay()
{
    Super::BeginPlay();
    checkf(WallComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(FloorComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(ColumnComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(StartComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
    checkf(EndComponent->GetStaticMesh(), TEXT("Mesh element must be set"));
}

void UGeometryComponent::PlaceWall(const float X, const float Y, const float R)
{
    WallComponent->AddInstance(FTransform(FRotator(0.0f, R, 0.0f), FVector(CellSize * X, CellSize * Y, 5.0f)));
}

void UGeometryComponent::PlaceColumn(const float X, const float Y)
{
    ColumnComponent->AddInstance(FTransform(FVector(CellSize * X, CellSize * Y, 5.0f)));
}

void UGeometryComponent::PlaceFloor(const float X, const float Y)
{
    FloorComponent->AddInstance(FTransform(FVector(CellSize * X, CellSize * Y, 0.0f)));
}

FIntVector UGeometryComponent::PlaceExit(const FIntVector &End, int Width, int Height)
{
    int8 X = 0;
    int8 Y = 0;
    if (End.X == 0)
    {
        X = End.X - 1;
        Y = End.Y;
    }
    else if (End.Y == 0)
    {
        X = End.X;
        Y = End.Y - 1;
    }
    else if (End.X == Height - 1)
    {
        X = End.X + 1;
        Y = End.Y;
    }
    else if (End.Y == Width - 1)
    {
        X = End.X;
        Y = End.Y + 1;
    }
    EndComponent->SetRelativeLocation(FVector(CellSize * X, CellSize * Y, 0.0f));
    return FIntVector(X, Y, 0);
}

void PlaceExit(const float X, const float Y, const float R)
{
}
