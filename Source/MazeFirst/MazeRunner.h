// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MazeRunner.generated.h"

class UCameraComponent;
class UInputComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class MAZEFIRST_API AMazeRunner : public ACharacter
{
    GENERATED_BODY()

public:
    AMazeRunner();
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

private:
    bool bHelpVisible = false;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCameraComponent* CameraComponent;

    void ShowHelp();
    void GenerateMaze();

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* HelpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* GenerateNewMazeAction;
};
