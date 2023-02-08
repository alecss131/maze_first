// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeHUD.h"
#include "MazeFirstGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMazeHUD::BeginPlay()
{
    Super::BeginPlay();
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(World->GetAuthGameMode()))
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

void AMazeHUD::OnSetPause(bool bPaused)
{
    if (bPaused)
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
