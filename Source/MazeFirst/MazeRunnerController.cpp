// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeRunnerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MazeFirstGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMazeRunnerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMazeRunnerController::PauseGame);
    }
}

void AMazeRunnerController::BeginPlay()
{
    Super::BeginPlay();
    if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 1);
    }
}

void AMazeRunnerController::PauseGame()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->SetPause.Broadcast(true);
    }
}
