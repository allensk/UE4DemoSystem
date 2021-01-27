// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CNGameState.generated.h"

class FCNItemStore;
class FCNChaStore;
class ACNObjectFactory;

/**
 * 
 */
UCLASS()
class CNBASE_API ACNGameState : public AGameState
{
	GENERATED_BODY()

public:
	ACNGameState();
	virtual ~ACNGameState() override;

	ACNObjectFactory* GetObjectFactory() { return ObjectFactory; }

protected:

	/**
	*
	*/
	virtual void PreInitializeComponents() override;

	UPROPERTY()
	ACNObjectFactory* ObjectFactory;
};
