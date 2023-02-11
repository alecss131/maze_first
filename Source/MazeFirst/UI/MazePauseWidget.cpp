// Copyright Alexey Morozov. All Rights Reserved.

#include "MazePauseWidget.h"
#include "MazeFirstGameModeBase.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMazePauseWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UMazePauseWidget::ResumeGame);
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMazePauseWidget::ExitGame);
    }
    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UMazePauseWidget::RestartMaze);
    }
    if (NewMazeButton)
    {
        NewMazeButton->OnClicked.AddDynamic(this, &UMazePauseWidget::NewMaze);
    }
}

void UMazePauseWidget::ResumeGame()
{
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(World->GetAuthGameMode()))
    {
        GameMode->SetPause.Broadcast(false);
    }
}

void UMazePauseWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMazePauseWidget::RestartMaze()
{
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(World->GetAuthGameMode()))
    {
        GameMode->RestartMaze.Broadcast();
        GameMode->SetPause.Broadcast(false);
    }
}

void UMazePauseWidget::NewMaze()
{
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(World->GetAuthGameMode()))
    {
        GameMode->RestartMaze.Broadcast();
        GameMode->GenerateNewMaze.Broadcast();
        GameMode->SetPause.Broadcast(false);
    }
}
