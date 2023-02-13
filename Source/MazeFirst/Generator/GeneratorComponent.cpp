// Copyright Alexey Morozov. All Rights Reserved.

#include "GeneratorComponent.h"

UGeneratorComponent::UGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGeneratorComponent::Build(uint8 Width, uint8 Height)
{
    TArray<FCell> In;
    In.Init({FCell()}, Width);
    Cells.Init({In}, Height);
    for (uint8 i = 0; i < Height; i++)
    {
        for (uint8 j = 0; j < Width; j++)
        {
            Cells[i][j].X = i;
            Cells[i][j].Y = j;
        }
    }
    RemoveWallsWithBackTracker();
    PlaceExit();
}

void UGeneratorComponent::Reset()
{
    Cells.Empty();
}

FIntVector UGeneratorComponent::GetEndLocation() const
{
    return End;
}

TArray<TArray<FCell>>& UGeneratorComponent::GetCells()
{
    return Cells;
}

void UGeneratorComponent::RemoveWallsWithBackTracker()
{
    const int Width = Cells[0].Num();
    const int Height = Cells.Num();
    FCell* Current = &Cells[0][0];
    Current->bHasBottom = false; //open start
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
        if (X < Height - 1 && !Cells[X + 1][Y].bIsVisited)
        {
            UnvisitedNeighbours.Add(&Cells[X + 1][Y]);
        }
        if (Y < Width - 1 && !Cells[X][Y + 1].bIsVisited)
        {
            UnvisitedNeighbours.Add(&Cells[X][Y + 1]);
        }
        if (UnvisitedNeighbours.Num() > 0)
        {
            FCell* Chosen = UnvisitedNeighbours[FMath::RandRange(0, UnvisitedNeighbours.Num() - 1)];
            RemoveWall(*Current, *Chosen);
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

void UGeneratorComponent::RemoveWall(FCell& A, FCell& B)
{
    if (A.X == B.X)
    {
        if (A.Y > B.Y)
        {
            A.bHasLeft = false;
        }
        else
        {
            B.bHasLeft = false;
        }
    }
    else
    {
        if (A.X > B.X)
        {
            A.bHasBottom = false;
        }
        else
        {
            B.bHasBottom = false;
        }
    }
}

void UGeneratorComponent::PlaceExit()
{
    const int Width = Cells[0].Num();
    const int Height = Cells.Num();
    FCell* Furthest = &Cells[0][0];
    for (uint8 i = 0; i < Width; i++)
    {
        if (Cells.Last()[i].Distance > Furthest->Distance)
        {
            Furthest = &Cells.Last()[i];
        }
        if (Cells[0][i].Distance > Furthest->Distance)
        {
            Furthest = &Cells[0][i];
        }
    }
    for (uint8 i = 0; i < Height; i++)
    {
        if (Cells[i].Last().Distance > Furthest->Distance)
        {
            Furthest = &Cells[i].Last();
        }
        if (Cells[i][0].Distance > Furthest->Distance)
        {
            Furthest = &Cells[i][0];
        }
    }
    End = FIntVector(Furthest->X, Furthest->Y, 0);
    if (Furthest->X == 0)
    {
        Furthest->bHasBottom = false;
    }
    else if (Furthest->Y == 0)
    {
        Furthest->bHasLeft = false;
    }
}
