// Copyright Alexey Morozov. All Rights Reserved.

#include "MenuController.h"

void AMenuController::BeginPlay()
{
    Super::BeginPlay();
    SetShowMouseCursor(true);
    SetInputMode(FInputModeUIOnly());
    FlushPressedKeys();
}
