// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MazeFirstTarget : TargetRules
{
	public MazeFirstTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("MazeFirst");
	}
}