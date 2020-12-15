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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Usable)
	bool IsUsable();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Usable)
	bool Use(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Usable)
	FText GetUseActionText();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Usable)
	bool BeginOutlineFocus();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Usable)
	bool EndOutlineFocus();
};