// Copyright Epic Games, Inc. All Rights Reserved.


#include "MazeFirstGameModeBase.h"
#include "MazeRunner.h"
#include "GameFramework/GameUserSettings.h"

AMazeFirstGameModeBase::AMazeFirstGameModeBase()
{
	DefaultPawnClass = AMazeRunner::StaticClass();
	if (GEngine)
	{
		UGameUserSettings * Settings = GEngine->GetGameUserSettings();
		Settings->SetVSyncEnabled(true);
		Settings->SetScreenResolution(FIntPoint(1280, 720));
		Settings->SetFullscreenMode(EWindowMode::Windowed);
		Settings->ApplySettings(false);
	}
}
