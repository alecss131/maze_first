// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeRunner.h"
#include "MazeFirstGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AMazeRunner::AMazeRunner()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(GetCapsuleComponent());
    CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    CameraComponent->bUsePawnControlRotation = true;
}

void AMazeRunner::ShowHelp()
{
    bHelpVisible ^= true;
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->ShowHelpPath.Broadcast(bHelpVisible);
    }
}

void AMazeRunner::GenerateMaze()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->GenerateNewMaze.Broadcast();
        GameMode->ResetPlayer(GetController());
    }
    bHelpVisible = false;
}

void AMazeRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMazeRunner::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMazeRunner::MoveRight);
    PlayerInputComponent->BindAxis("LookTurn", this, &AMazeRunner::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AMazeRunner::AddControllerPitchInput);
    PlayerInputComponent->BindAction("ShowHelp", IE_Pressed, this, &AMazeRunner::ShowHelp);
    PlayerInputComponent->BindAction("GenerateNewMaze", IE_Pressed, this, &AMazeRunner::GenerateMaze);

}

void AMazeRunner::MoveForward(float Axis)
{
    AddMovementInput(GetActorForwardVector(), Axis);
}

void AMazeRunner::MoveRight(float Axis)
{
    AddMovementInput(GetActorRightVector(), Axis);
}
