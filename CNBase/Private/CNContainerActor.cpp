// Fill out your copyright notice in the Description page of Project Settings.
#include "CNContainerActor.h"
#include "GameFramework/PlayerController.h"
#include "CNPlayerController.h"
#include "CNInventoryManager.h"

ACNContainerActor::ACNContainerActor()
{
	InventoryComponent = CreateDefaultSubobject<UCNEquipsComponent>("InventoryComponent");

	Name = TEXT("Default Container Name");
	SlotsNum = 4;
	SlotsPerRow = 4;
	bCanStore = true;
}

bool ACNContainerActor::Use_Implementation(APlayerController* PlayerController)
{
	Super::Use_Implementation(PlayerController);

	if (!HasAuthority()) {
		return false;
	}

	PlayerStates.Add(PlayerController->PlayerState);

	if (auto Player = Cast<ACNPlayerController>(PlayerController)) {
		Player->ServerUseContainer(this);
	}
	
	return true;
}

bool ACNContainerActor::Loot()
{
	if (!HasAuthority()) {
		return false;
	}

	for (auto x : PlayerStates) {
		auto OwnerController = x->GetOwner();
		if (auto Player = Cast<ACNPlayerController>(OwnerController)) {
			// Close container UI
			Player->ServerCloseContainer();
		}
	}

	SetLifeSpan(30);

	return true;
}

//void ACNContainerActor::InitializeInventory()
//{
//	if (!HasAuthority()) {
//		return;
//	}
//
//	
//}
