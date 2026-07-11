// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MobCombat_RPG : ModuleRules
{
	public MobCombat_RPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayTags", 
			"GameplayTasks", 
			"AnimGraphRuntime", 
			"MotionWarping", 
			"Niagara", 
			"NavigationSystem", 
			"UMG", 
			"CommonUI", 
			"GameplayAbilities", 
			"AIModule", 
			"CommonInput"
		});
		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
