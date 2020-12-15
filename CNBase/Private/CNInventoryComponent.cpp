// Fill out your copyright notice in the Description page of Project Settings.


#include "CNInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Net/DataChannel.h"
#include "Engine/ActorChannel.h"
#include "Kismet/GameplayStatics.h"

#include "CNGameLog.h"
#include "CNItem.h"
#include "CNObjectFactoryLib.h"

// Sets default values for this component's properties
UCNInventoryComponent::UCNInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// ...

	ItemMaxAmount = 99;
	bReplicates = false;
}


void UCNInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Only owner connection
	// DOREPLIFETIME_CONDITION(UCNInventoryComponent, Items, ELifetimeCondition::COND_OwnerOnly);
}

bool UCNInventoryComponent::ReplicateSubobjects(UActorChannel * Channel, FOutBunch * Bunch, FReplicationFlags * RepFlags)
{
	//bool Ret = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	//if (RepFlags->bNetInitial) {
	//	// As items are created dynamically, you can't depend on normal array replication.
	//	for (auto& Ele : Items) {
	//		UE_LOG(CNLog, Log, TEXT("Replicate Item Initial"));
	//		Ret |= Channel->ReplicateSubobject(Ele, *Bunch, *RepFlags);
	//	}
	//}

	//return Ret;
	return Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
}

// Called when the game starts
void UCNInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwnerRole() == ROLE_Authority) {
		LoadItems();
	}
}


// Called every frame
void UCNInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}

void UCNInventoryComponent::LoadItems()
{
	for (auto& x : InitDatas) {

		auto Item = UCNObjectFactoryLib::FindItemByName(UGameplayStatics::GetGameState(GetWorld()),
			x.BaseName, (int)x.Level);
		if (Item) {
			FCNObjectIndex Index(Item->GetCurBaseAttri().Index);
			FCNItemInfo ItemInfo{ Index, x.Amount };
			ItemInfos.Push(ItemInfo);
		}
		else {
			UE_LOG(CNLog, Log, TEXT("%s Load Item %s failed"),
				*GetOwner()->GetName(),
				*x.BaseName);
		}
	}
}

void UCNInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(CNLog, Verbose, TEXT("UCNInventoryComponent::InitializeComponent"));
}

void UCNInventoryComponent::ClientSetItemNum_Implementation(UCNItem * Item, int Num)
{
	//for (auto& Ele : Items) {
	//	if (Item == Ele) {
	//		Ele->SetAmount(Num);
	//		break;
	//	}
	//}
}

void UCNInventoryComponent::ClientRemoveItem_Implementation(UCNItem * Item)
{
	//for (auto& Ele : Items) {
	//	if (Item == Ele) {
	//		Items.RemoveSingle(Item);
	//		OnAddOrRemoveItem.Broadcast(false, Item);
	//		break;
	//	}
	//}

	OnAddOrRemoveItem.Broadcast(false, Item);
}

void UCNInventoryComponent::ServerChangeItemNum_Implementation(UCNItem* Item, int Num)
{
	//// Unchange and return
	//if (!Num) {
	//	return;
	//}

	//bool bInInventory = false;
	//for (auto& Ele : Items) {
	//	if (Item == Ele) {
	//		bInInventory = true;
	//		break;
	//	}
	//}

	//int Amount = Item->GetAmount();
	//if (bInInventory) {
	//	// Out scope
	//	if (Num + Amount >= ItemMaxAmount) {
	//		Item->SetAmount(ItemMaxAmount);
	//	}
	//	// In scope
	//	else if (Num + Amount > 0) {
	//		Item->SetAmount(Num + Amount);
	//	}

	//	// Num reach 0, remove Item
	//	// Let it be auto-destroyed
	//	else {
	//		// Clear UI item ref
	//		ClientRemoveItem(Item);
	//		// Clear item reference
	//		Items.RemoveSingle(Item);
	//	}
	//	
	//	// GetOwner()->GetNetDriver()->FlushActorDormancy()
	//	// ClientSetItemNum(Item, Item->GetAmount());
	//	
	//}
	//// Create Item
	////else {
	////	// Out scope
	////	if (Num + Amount > ItemMaxAmount) {
	////		Amount = ItemMaxAmount;
	////	}

	////	ensure(Num + Amount > 0);

	////	// 
	////	auto Base = Item->GetCurBaseAttri();
	////	auto p = NewObject<UCNItem>();
	////	p->SetBasicData(Item->GetBasicName(), Item->GetLevel());
	////	p->SetAmount(Amount);
	////	Items.Add(p);
	////}
}

bool UCNInventoryComponent::ServerChangeItemNum_Validate(UCNItem* Item, int Num)
{
	return true;
}

void UCNInventoryComponent::ChangeItemNum(UCNItem* Item, int Num)
{
	// Skip nullptr and no-change
	if (!Item || !Num) {
		return;
	}

	// Bad parameter
	if (Item->GetAmount() + Num < 0) {
		return;
	}

	ensure(Item->GetAmount() + Num >= 0);

	ServerChangeItemNum(Item, Num);
}

void UCNInventoryComponent::ServerUseItem_Implementation(int Slot)
{
	return;
}


bool UCNInventoryComponent::ServerUseItem_Validate(int Slot)
{
	return true;
}
