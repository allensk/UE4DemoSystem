// Fill out your copyright notice in the Description page of Project Settings.


#include "CNObjectFactoryLib.h"
#include "Engine/Engine.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"

#include "CNGameState.h"
#include "CNObjectFactory.h"
#include "CNItemStore.h"

#pragma optimize( "", off )

int UCNObjectFactoryLib::GetItemID(const FString& Name)
{
	static FCNItemStore ItemStore;
	int ID = ItemStore.GetObjectID(Name);
	return ID;
}

UCNItem* UCNObjectFactoryLib::FindItemByID(AGameStateBase* State, FCNObjectIndex Index)
{
	static ACNObjectFactory* TmpFactory = nullptr;
	
	// Assign TmpGameState if it is invalid
	if (!(TmpFactory && TmpFactory->IsValidLowLevel()) && State) {
		auto CNState = Cast<ACNGameState>(State);
		if (CNState) {
			auto Factory = CNState->GetObjectFactory();
			if (Factory) {
				TmpFactory = Factory;
			}
		}
	}

	// 
	if (TmpFactory && TmpFactory->IsValidLowLevel()) {
		return TmpFactory->FindItem(Index);
	}
	
	return nullptr;
}

UCNItem* UCNObjectFactoryLib::FindItemByName(AGameStateBase* State, FString Name, int Level)
{
	int ID = GetItemID(Name);
	if (ID) {
		return FindItemByID(State, FCNObjectIndex{ID, Level});
	}
	
	return nullptr;
}

UCNCha* UCNObjectFactoryLib::FindCharacterByID(AGameStateBase* State, FCNObjectIndex Index)
{
	return nullptr;
}


#pragma optimize( "", on )