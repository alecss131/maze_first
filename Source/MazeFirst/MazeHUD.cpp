// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeHUD.h"
#include "MazeFirstGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMazeHUD::BeginPlay()
{
    Super::BeginPlay();
    if (!GetWorld()) return;
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->SetPause.AddUObject(this, &AMazeHUD::OnSetPause);
    }
    if (PauseWidgetClass)
    {
        PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
        if (PauseWidget)
        {
            PauseWidget->AddToViewport();
            PauseWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    if (HudWidgetClass)
    {
        HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
        if (HudWidget)
        {
            HudWidget->AddToViewport();
        }
    }
}

void AMazeHUD::OnSetPause(bool Paused)
{
    if (Paused)
    {
        PauseWidget->SetVisibility(ESlateVisibility::Visible);
        HudWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        PauseWidget->SetVisibility(ESlateVisibility::Hidden);
        HudWidget->SetVisibility(ESlateVisibility::Visible);
    }
}
