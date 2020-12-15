// Fill out your copyright notice in the Description page of Project Settings.


#include "CNGameState.h"
#include "CNGameLog.h"

#include "CNDBConnection.h"
#include "CNItemStore.h"
#include "CNChaStore.h"

#include "CNObjectFactory.h"

ACNGameState::ACNGameState()
{
	UE_LOG(CNLog, Verbose, TEXT("Construct ACNGameState"));
	ObjectFactory = CreateDefaultSubobject<ACNObjectFactory>("ObjectFactory");
}

ACNGameState::~ACNGameState()
{
	UE_LOG(CNLog, Verbose, TEXT("Destruct ACNGameState"));
}

void ACNGameState::PreInitializeComponents()
{
	
}
