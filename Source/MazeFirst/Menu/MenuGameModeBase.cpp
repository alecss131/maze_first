// Copyright Alexey Morozov. All Rights Reserved.

#include "MenuGameModeBase.h"
#include "MenuController.h"
#include "MenuHUD.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"

AMenuGameModeBase::AMenuGameModeBase()
{
    HUDClass = AMenuHUD::StaticClass();
    PlayerControllerClass = AMenuController::StaticClass();
    if (GEngine)
    {
        UGameUserSettings* Settings = GEngine->GetGameUserSettings();
        Settings->SetVSyncEnabled(true);
        Settings->SetScreenResolution(FIntPoint(1280, 720));
        Settings->SetFullscreenMode(EWindowMode::Windowed);
        Settings->ApplySettings(false);
    }
}
