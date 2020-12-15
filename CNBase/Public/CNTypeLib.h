// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNAttriBase.h"
#include "CNTypeLib.generated.h"

/**
 * 
 */
UCLASS()
class CNBASE_API UCNTypeLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Get key to retrive text in string table
	 */
	UFUNCTION(BlueprintCallable, Category = UCNTypeLib)
	static FName GetLevelSTKey(ECNObjectLevel Level);
};
