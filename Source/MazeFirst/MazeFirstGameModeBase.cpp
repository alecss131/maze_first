// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeFirstGameModeBase.h"
#include "MazeRunner.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "MazeHUD.h"
#include "MazeRunnerController.h"

AMazeFirstGameModeBase::AMazeFirstGameModeBase()
{
    DefaultPawnClass = AMazeRunner::StaticClass();
    HUDClass = AMazeHUD::StaticClass();
    PlayerControllerClass = AMazeRunnerController::StaticClass();
    if (GEngine)
    {
        UGameUserSettings* Settings = GEngine->GetGameUserSettings();
        Settings->SetVSyncEnabled(true);
        Settings->SetScreenResolution(FIntPoint(1280, 720));
        Settings->SetFullscreenMode(EWindowMode::Windowed);
        Settings->ApplySettings(false);
    }
}
