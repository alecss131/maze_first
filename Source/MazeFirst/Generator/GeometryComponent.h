// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GeometryComponent.generated.h"

class UInstancedStaticMeshComponent;
class UStaticMeshComponent;
struct FCell;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEFIRST_API UGeometryComponent : public USceneComponent
{
	GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, Category = Components)
    UInstancedStaticMeshComponent* WallComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Components)
    UInstancedStaticMeshComponent* FloorComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Components)
    UInstancedStaticMeshComponent* ColumnComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Components)
    UStaticMeshComponent* StartComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Components)
    UStaticMeshComponent* EndComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = Parameters, meta = (ClampMin = 0.0))
    float CellSize = 400.0f;

public:	
	UGeometryComponent();

    float GetCellSize() const;
    void Reset();
    void Build(const TArray<TArray<FCell>> &Cells, const FIntVector &End);
    
protected:
	virtual void BeginPlay() override;

private:
    void PlaceWall(const float X, const float Y, const float R);
    void PlaceColumn(const float X, const float Y);
    void PlaceFloor(const float X, const float Y);
    FIntVector PlaceExit(const FIntVector &End, int Width, int Height);
};
