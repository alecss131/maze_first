// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MazeRunner.generated.h"

class UCameraComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowHelpPath, bool)
DECLARE_MULTICAST_DELEGATE(FOnGenerateNewMaze)

UCLASS()
class MAZEFIRST_API AMazeRunner : public ACharacter
{
	GENERATED_BODY()

public:
	AMazeRunner();
    
    FOnShowHelpPath ShowHelpPath;
    FOnGenerateNewMaze GenerateNewMaze;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;
private:
    bool bHelpVisible = false;
    FVector InitialPosition;
    
    void ShowHelp();
    void GenerateMaze();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Axis);
    void MoveRight(float Axis);
};
