// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TFE : ModuleRules
{
	public TFE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
