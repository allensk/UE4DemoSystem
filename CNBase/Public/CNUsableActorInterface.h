// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CNUsableActorInterface.generated.h"

class APlayerController;

UINTERFACE(MinimalAPI, Blueprintable)
class UCNUsableActorInterface : public UInterface
{
	GENERATED_BODY()
};

class ICNUsableActorInterface
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Usable)
	bool IsUsable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Usable)
	bool Use(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Usable)
	FText GetUseActionText();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Usable)
	bool BeginOutlineFocus();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Usable)
	bool EndOutlineFocus();
};