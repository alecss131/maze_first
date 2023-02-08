// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeFirstGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetPause, bool)
DECLARE_MULTICAST_DELEGATE(FOnShowHelpPath)
DECLARE_MULTICAST_DELEGATE(FOnGenerateNewMaze)
DECLARE_MULTICAST_DELEGATE(FOnRestartMaze)

UCLASS()
class MAZEFIRST_API AMazeFirstGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMazeFirstGameModeBase();

    FOnShowHelpPath ShowHelpPath;
    FOnGenerateNewMaze GenerateNewMaze;
    FOnSetPause SetPause;
    FOnRestartMaze RestartMaze;
};
