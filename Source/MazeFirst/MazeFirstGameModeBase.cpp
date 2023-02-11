// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeFirstGameModeBase.h"
#include "Player/MazeRunner.h"
#include "UI/MazeHUD.h"
#include "Player/MazeRunnerController.h"

AMazeFirstGameModeBase::AMazeFirstGameModeBase()
{
    DefaultPawnClass = AMazeRunner::StaticClass();
    HUDClass = AMazeHUD::StaticClass();
    PlayerControllerClass = AMazeRunnerController::StaticClass();
}
