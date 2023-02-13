// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

class USceneComponent;
class UGeometryComponent;
class UHelpComponent;
class UGeneratorComponent;

UCLASS()
class MAZEFIRST_API AMazeGenerator : public AActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
    USceneComponent* SceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
    UGeometryComponent* GeometryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
    UHelpComponent* HelpComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
    UGeneratorComponent* GeneratorComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters, meta = (ClampMin = 5, ClampMax = 100, AllowPrivateAccess = true))
    uint8 Width = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters, meta = (ClampMin = 5, ClampMax = 100, AllowPrivateAccess = true))
    uint8 Height = 10;

public:
    AMazeGenerator();

protected:

    UFUNCTION(BlueprintCallable)
    void GenerateMaze();

    virtual void BeginPlay() override;

private :
    void ResetMaze();
};
