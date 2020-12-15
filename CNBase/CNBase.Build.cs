// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CNBase : ModuleRules
{
	public CNBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                "CNBase/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "CNBase/Private"
            });


        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "SQLiteCore" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
