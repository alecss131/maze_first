// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MazeRunner.generated.h"

class UCameraComponent;
class UInputComponent;


UCLASS()
class MAZEFIRST_API AMazeRunner : public ACharacter
{
    GENERATED_BODY()

public:
    AMazeRunner();

private:
    bool bHelpVisible = false;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCameraComponent* CameraComponent;

    void ShowHelp();
    void GenerateMaze();

public:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void MoveForward(float Axis);
    void MoveRight(float Axis);
};
