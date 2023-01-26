// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePauseWidget.h"

#include "MazeFirstGameModeBase.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMazePauseWidget::NativeConstruct()
{
    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UMazePauseWidget::ResumeGame);
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMazePauseWidget::ExitGame);
    }
}

void UMazePauseWidget::ResumeGame()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->SetPause.Broadcast(false);
    }
}

void UMazePauseWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
