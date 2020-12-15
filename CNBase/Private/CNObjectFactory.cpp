// Fill out your copyright notice in the Description page of Project Settings.

#include "CNObjectFactory.h"

#include "CNItem.h"
#include "CNCha.h"
#include "CNGameLog.h"

// Sets default values
ACNObjectFactory::ACNObjectFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACNObjectFactory::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACNObjectFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UCNItem* ACNObjectFactory::FindItem(FCNObjectIndex Index)
{
	if (auto pObject = Objects.Find(Index)) {
		return dynamic_cast<UCNItem*>(*pObject);
	}
	else {
		// Create new object
		auto Object = NewObject<UCNItem>();
		Object->SetBasicDataByID(Index.ID, (ECNObjectLevel) Index.Level);
		Objects.Add(Index, Object);
		UE_LOG(CNLog, Log, TEXT("ACNObjectFactory::FindItem %s"), *Object->GetBasicName());
		return Object;
	}
}

UCNCha * ACNObjectFactory::FindCharacter(FCNObjectIndex Index)
{
	return nullptr;
}

