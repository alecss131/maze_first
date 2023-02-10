// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeFirstGameModeBase.h"
#include "MazeRunner.h"
#include "MazeHUD.h"
#include "MazeRunnerController.h"

AMazeFirstGameModeBase::AMazeFirstGameModeBase()
{
    DefaultPawnClass = AMazeRunner::StaticClass();
    HUDClass = AMazeHUD::StaticClass();
    PlayerControllerClass = AMazeRunnerController::StaticClass();
}
