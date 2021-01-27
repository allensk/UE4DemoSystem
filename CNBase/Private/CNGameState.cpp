// Fill out your copyright notice in the Description page of Project Settings.


#include "CNGameState.h"
#include "CNGameLog.h"

#include "CNDBConnection.h"
#include "CNItemStore.h"
#include "CNChaStore.h"

#include "CNObjectFactory.h"

ACNGameState::ACNGameState()
{
	UE_LOG(CNLog, Log, TEXT("Construct ACNGameState"));
	// Here using object function as we don't call SpawnActor, and UPROPERTY() is needed.
	ObjectFactory = CreateDefaultSubobject<ACNObjectFactory>("ObjectFactory");
	if (!ObjectFactory || !ObjectFactory->IsValidLowLevel()) {
		UE_LOG(CNLog, Error, TEXT("Create ObjectFactory failed"));
	}
}

ACNGameState::~ACNGameState()
{
	UE_LOG(CNLog, Log, TEXT("Destruct ACNGameState"));
}

void ACNGameState::PreInitializeComponents()
{
	
}
