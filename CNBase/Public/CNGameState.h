// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CNGameState.generated.h"

class FCNItemStore;
class FCNChaStore;
class ACNObjectFactory;

/**
 * 
 */
UCLASS()
class CNBASE_API ACNGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACNGameState();
	~ACNGameState();

	ACNObjectFactory* GetObjectFactory() { return ObjectFactory; }

protected:

	/**
	*
	*/
	virtual void PreInitializeComponents() override;

	// UPROPERTY(BlueprintReadOnly, Category = "CNHelp")
	ACNObjectFactory* ObjectFactory;
};
