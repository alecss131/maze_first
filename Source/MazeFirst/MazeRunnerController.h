// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MazeRunnerController.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class MAZEFIRST_API AMazeRunnerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;

public:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* PauseAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* HelpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* GenerateNewMazeAction;

private:
    void PauseGame();
    void ShowHelp();
    void GenerateMaze();

    UFUNCTION()
    void OnSetPause(bool Paused);
};
