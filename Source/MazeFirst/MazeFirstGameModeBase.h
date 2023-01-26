// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeFirstGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetPause, bool)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowHelpPath, bool)
DECLARE_MULTICAST_DELEGATE(FOnGenerateNewMaze)

UCLASS()
class MAZEFIRST_API AMazeFirstGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMazeFirstGameModeBase();
    void ResetPlayer(AController* Controller);

    FOnShowHelpPath ShowHelpPath;
    FOnGenerateNewMaze GenerateNewMaze;
    FOnSetPause SetPause;
};
