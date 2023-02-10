// Copyright Alexey Morozov. All Rights Reserved.

#include "MenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMenuUserWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnExit);
    }
    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnPlay);
    }
}

void UMenuUserWidget::OnExit()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMenuUserWidget::OnPlay()
{
    UGameplayStatics::OpenLevel(this, LevelName);
}
