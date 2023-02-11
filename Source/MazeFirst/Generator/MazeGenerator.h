// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Cell.h"
#include "MazeGenerator.generated.h"

class USceneComponent;
class UInstancedStaticMeshComponent;
class UStaticMeshComponent;
class USplineComponent;
class UNiagaraComponent;

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

    UPROPERTY(EditAnywhere, Category = "Parameters")
    FName SplineName = "spline_path";

    UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "0.0"))
    float CellSize = 400.0f;

    UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "5", ClampMax = "100"))
    uint8 Width = 23;

    UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "5", ClampMax = "100"))
    uint8 Height = 15;

public:
    AMazeGenerator();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USplineComponent* SplineComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UNiagaraComponent* Path;

    UFUNCTION(BlueprintCallable)
    void GenerateMaze();

    virtual void BeginPlay() override;

private :
    void RemoveWallsWithBackTracker();
    void RemoveWall(FCell &A, FCell &B);
    void PlaceExit();
    void BuildGeometry();
    void PlaceColumn(const float X, const float Y);
    void PlaceFloor(const float X, const float Y);
    void AddPoint(const uint8 X, const uint8 Y);
    void PlaceWall(const float X, const float Y, const float R);
    void FindPath();
    void SetShowPath(bool bShow);
    void ResetMaze();

    UFUNCTION()
    void ShowPath();

    UFUNCTION()
    void HidePath();

    FIntVector End;
    FIntVector Exit;
    TArray<TArray<FCell>> Cells;
};
