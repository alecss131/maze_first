// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

class USceneComponent;
class UInstancedStaticMeshComponent;
class UStaticMeshComponent;
class USplineComponent;
struct FCell;

UCLASS()
class MAZEFIRST_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
    
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UInstancedStaticMeshComponent* WallComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UInstancedStaticMeshComponent* FloorComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UInstancedStaticMeshComponent* ColumnComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StartComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* EndComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USplineComponent* SplineComponent;
	
	UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "0.0"))
	float CellSize = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "5", ClampMax = "100"))
	uint8 Width = 23;

	UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "5", ClampMax = "100"))
	uint8 Height = 15;
	
public:	
	AMazeGenerator();

	UFUNCTION(BlueprintCallable)
	void GenerateMaze();

protected:
	virtual void BeginPlay() override;

private :
	void RemoveWallsWithBackTracker(FCell **Cells);
	void RemoveWall(FCell *A, FCell *B);
	FIntVector PlaceExit(FCell **Cells);
	void BuildGeometry(FCell **Cells, FIntVector Exit);
	void PlaceColumn(const float X, const float Y);
	void PlaceFloor(const float X, const float Y);
    void AddPoint(const uint8 X, const uint8 Y);
	void PlaceWall(const float X, const float Y, const float R);
    void FindPath(FCell **Cells);
    FIntVector End;
};
