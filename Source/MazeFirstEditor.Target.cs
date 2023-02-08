// Copyright Alexey Morozov. All Rights Reserved.

using UnrealBuildTool;

public class MazeFirstEditorTarget : TargetRules
{
	public MazeFirstEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("MazeFirst");
	}
}