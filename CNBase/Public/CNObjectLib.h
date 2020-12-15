// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNObjectLib.generated.h"

class UTexture2D;

/**
 * 
 */
UCLASS()
class CNBASE_API UCNObjectLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Get the reference path to a object
	 */
	UFUNCTION(BlueprintCallable, Category = ObjectLib)
	static FString GetObjectPath(const UObject* Obj);

	/**
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category = ObjectLib)
	static UTexture2D* LoadTexture2DFromPath(const FString& Path);
};
