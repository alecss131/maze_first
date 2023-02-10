// Copyright Alexey Morozov. All Rights Reserved.

#include "MenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (!GetWorld()) return;
    if (const auto MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass))
    {
        MenuWidget->AddToViewport();
    }
}
