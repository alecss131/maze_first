// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cell.h"
#include "GeneratorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEFIRST_API UGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGeneratorComponent();

    void Build(uint8 Width, uint8 Height);
    void Reset();
    FIntVector GetEndLocation() const;
    TArray<TArray<FCell>>& GetCells();

private:
    void RemoveWallsWithBackTracker();
    void RemoveWall(FCell &A, FCell &B);
    void PlaceExit();
    
    FIntVector End = FIntVector::ZeroValue;
    TArray<TArray<FCell>> Cells;
};
