// Fill out your copyright notice in the Description page of Project Settings.


#include "CNObjectFactoryLib.h"
#include "Engine/Engine.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "CNItem.h"
#include "CNCha.h"

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
	
	//static AGameStateBase* TmpState = nullptr;
	//// Every time reassign pointer (State is a long time object, one state for one game)
	//if (!TmpState || TmpState != State) {
	//}

	// Assign TmpGameState if it is invalid
	if (State &&
		(!TmpFactory ||
		(TmpFactory && !TmpFactory->IsValidLowLevel()))
		) {
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

		ensure(TmpFactory);

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

bool UCNObjectFactoryLib::IsItemInfoValid(const FCNItemInfo& ItemInfo)
{
	return ItemInfo.Index.IsValid();
}


#pragma optimize( "", on )