// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNAttriBase.h"
#include "CNObjectFactoryLib.generated.h"

class UCNItem;
class UCNCha;
class AGameStateBase;

/**
 * 
 */
UCLASS()
class CNBASE_API UCNObjectFactoryLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = ObjectFactoryLib)
	static int GetItemID(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = ObjectFactoryLib)
	static UCNItem* FindItemByID(AGameStateBase* State, FCNObjectIndex Index);

	UFUNCTION(BlueprintCallable, Category = ObjectFactoryLib)
	static UCNItem* FindItemByName(AGameStateBase* State, FString Name, int Level);

	UFUNCTION(BlueprintCallable, Category = ObjectFactoryLib)
	static UCNCha* FindCharacterByID(AGameStateBase* State, FCNObjectIndex Index);

	UFUNCTION(BlueprintCallable, Category = ObjectFactoryLib)
	static bool IsItemInfoValid(const FCNItemInfo& ItemInfo);
};
