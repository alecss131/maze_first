// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MazeFirstTarget : TargetRules
{
	public MazeFirstTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "MazeFirst" });
	}
}