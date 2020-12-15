// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNActorLib.generated.h"

class AActor;

/**
 * 
 */
UCLASS(meta = (ScriptName = "GenericActorLibrary"))
class CNBASE_API UCNActorLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
public:
	
	/*
	* Find the nearest actor among a set of actors
	* @Param Origin the actor to measure length
	* @Param Tag If pass in a tag, the function will filter by tag
	*/
	UFUNCTION(BlueprintCallable, Category = Actor)
	static AActor* GetNearestActor(AActor* Origin, TArray<AActor*> Actors, FName Tag = "");
};
