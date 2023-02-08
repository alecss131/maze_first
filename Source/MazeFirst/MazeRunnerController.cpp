// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeRunnerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MazeFirstGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMazeRunnerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (const auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMazeRunnerController::PauseGame);
        EnhancedInputComponent->BindAction(HelpAction, ETriggerEvent::Triggered, this, &AMazeRunnerController::ShowHelp);
    }
}

void AMazeRunnerController::BeginPlay()
{
    Super::BeginPlay();
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(World->GetAuthGameMode()))
    {
        GameMode->SetPause.AddUObject(this, &AMazeRunnerController::OnSetPause);
        GameMode->RestartMaze.AddUObject(this, &AMazeRunnerController::ResetPlayer);
    }
    if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 1);
    }
}

void AMazeRunnerController::PauseGame()
{
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(World)))
    {
        GameMode->SetPause.Broadcast(true);
    }
}

void AMazeRunnerController::ShowHelp()
{
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(World)))
    {
        GameMode->ShowHelpPath.Broadcast();
    }
}

void AMazeRunnerController::OnSetPause(bool bPaused)
{
    SetPause(bPaused);
    SetShowMouseCursor(bPaused);
    if (bPaused)
    {
        SetInputMode(FInputModeUIOnly());
        FlushPressedKeys();
    }
    else
    {
        SetInputMode(FInputModeGameOnly());
    }
}

void AMazeRunnerController::ResetPlayer()
{
    if (const auto MazePawn = GetPawn())
    {
        MazePawn->Reset();
    }
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(World)))
    {
        GameMode->RestartPlayer(this);
    }
}
