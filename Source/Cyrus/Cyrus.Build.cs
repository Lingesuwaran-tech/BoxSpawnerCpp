// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cyrus : ModuleRules
{
	public Cyrus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"HTTP", "Json", "JsonUtilities", "UMG" });
	}
}
