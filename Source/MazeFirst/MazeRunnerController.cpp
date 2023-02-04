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
        EnhancedInputComponent->BindAction(HelpAction, ETriggerEvent::Triggered, this, &AMazeRunnerController::ShowHelp);
        EnhancedInputComponent->BindAction(GenerateNewMazeAction, ETriggerEvent::Triggered, this, &AMazeRunnerController::GenerateMaze);
    }
}

void AMazeRunnerController::BeginPlay()
{
    Super::BeginPlay();
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->SetPause.AddUObject(this, &AMazeRunnerController::OnSetPause);
    }
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

void AMazeRunnerController::ShowHelp()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->ShowHelpPath.Broadcast();
    }
}

void AMazeRunnerController::GenerateMaze()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->GenerateNewMaze.Broadcast();
        GameMode->ResetPlayer(this);
    }
}

void AMazeRunnerController::OnSetPause(bool Paused)
{
    SetPause(Paused);
    SetShowMouseCursor(Paused);
    if (Paused)
    {
        SetInputMode(FInputModeUIOnly());
        FlushPressedKeys();
    }
    else
    {
        SetInputMode(FInputModeGameOnly());
    }
}
