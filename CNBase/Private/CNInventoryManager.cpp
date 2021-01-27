// Fill out your copyright notice in the Description page of Project Settings.


#include "CNInventoryManager.h"
#include "CNInventoryComponent.h"
#include "CNPlayerController.h"
#include "CNObjectFactoryLib.h"
#include "CNItem.h"
#include "Kismet/GameplayStatics.h"
#include "CNGameLog.h"

// Sets default values for this component's properties
UCNInventoryManager::UCNInventoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UCNInventoryManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UCNInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCNInventoryManager::BPInitialize(UCNInventoryComponent* InventoryComp,
	UCNEquipsComponent* EquipsComp)
{
	this->PlayerInventory = InventoryComp;
	this->PlayerEquipment = EquipsComp;
}

void UCNInventoryManager::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(CNLog, Verbose, TEXT("UCNInventoryManager::InitializeComponent"));
}

void UCNInventoryManager::ClientOpenContainer_Implementation(ACNContainerActor* Container,
	const TArray<FCNItemInfo>& ItemInfos)
{
	BPOpenContainer(Container, ItemInfos);
}

void UCNInventoryManager::ClientCloseContainer_Implementation(ACNContainerActor* Container)
{
	BPCloseContainer(Container);
}

void UCNInventoryManager::OpenContainer(ACNContainerActor* Container)
{
	ClientOpenContainer(Container, Container->InventoryComponent->GetItems());
	CurrentContainer = Container;
}

void UCNInventoryManager::UseContainer(ACNContainerActor* Container)
{
	if (Container == CurrentContainer) {
		CloseContainer();
	}
	else {
		OpenContainer(Container);
	}
}

void UCNInventoryManager::CloseContainer()
{
	if (CurrentContainer) {
		ClientCloseContainer(CurrentContainer);
		CurrentContainer = nullptr;
	}
}

void UCNInventoryManager::ChangItemAmount(UCNInventoryComponent * InventoryComp, int SlotPos, int Amount)
{
	FCNItemInfo Item = InventoryComp->GetItem(SlotPos);
	// Check Amount
	if (!Amount) {
		return;
	}

	// Check valid
	if (!Item.Index.IsValid()) {
		return;
	}

	if (Item.Amount <= 0) {
		RemoveItem(InventoryComp, SlotPos);
		return;
	}

	Item.Amount += Amount;
	if (Item.Amount >= InventoryComp->GetItemMaxAmount()) {
		Item.Amount = InventoryComp->GetItemMaxAmount();
	}

	AddItem(InventoryComp, SlotPos, Item);
}

void UCNInventoryManager::MoveItemInInventory(int FromSlotPos, int ToSlotPos)
{
	MoveItem(PlayerInventory, FromSlotPos, PlayerInventory, ToSlotPos);
}

void UCNInventoryManager::MoveItemInContainer(int FromSlotPos, int ToSlotPos)
{
	if (CurrentContainer) {
		MoveItem(CurrentContainer->GetInventory(),
			FromSlotPos,
			CurrentContainer->GetInventory(),
			ToSlotPos);
	}
}

void UCNInventoryManager::TakeContainerItem(int FromContainerSlotPos, int ToInventorySlotPos)
{
	if (CurrentContainer) {
		MoveItem(CurrentContainer->GetInventory(),
			FromContainerSlotPos,
			PlayerInventory,
			ToInventorySlotPos);
	}
}

void UCNInventoryManager::DepositContainerItem(int FromInventorySlotPos, int ToContainerSlotPos)
{
	if (CurrentContainer) {
		MoveItem(PlayerInventory,
			FromInventorySlotPos,
			CurrentContainer->GetInventory(),
			ToContainerSlotPos);
	}
}

void UCNInventoryManager::UnEquipItem(int FromEquipmentSlotPos, int ToInventorySlotPos)
{
	MoveItem(PlayerEquipment,
		FromEquipmentSlotPos,
		PlayerInventory,
		ToInventorySlotPos);
}

void UCNInventoryManager::AddItemAmount(UCNInventoryComponent * InventoryComp, int SlotPos, int Amount)
{
	ChangItemAmount(InventoryComp, SlotPos, Amount);
}

void UCNInventoryManager::ReduceItemAmount(UCNInventoryComponent * InventoryComp, int SlotPos, int Amount)
{
	ChangItemAmount(InventoryComp, SlotPos, -Amount);
}

bool UCNInventoryManager::FindAndMoveToStack(UCNInventoryComponent* FromInventoryComp, int FromSlotPos,
	UCNInventoryComponent* ToInventoryComp, const FCNItemInfo& ItemInfo)
{
	int Index = 0;
	bool Found = ToInventoryComp->FindItem(ItemInfo, Index);
	if (Found) {
		AddItemAmount(ToInventoryComp, Index, ItemInfo.Amount);
		RemoveItem(FromInventoryComp, FromSlotPos);

		return true;
	}

	return false;
}

void UCNInventoryManager::SplitItem(UCNInventoryComponent * InventoryComp, int FromSlotPos, int ToSlotPos, int Amount)
{

}

void UCNInventoryManager::ClientClearInventory_Implementation()
{
	BPClearInventory();
}

void UCNInventoryManager::ClientClearContainer_Implementation()
{
	BPClearContainer();
}

void UCNInventoryManager::RefreshInventory()
{
	ClientClearInventory();

	auto& ItemInfos = PlayerInventory->GetItems();
	for (int i = 0; i < ItemInfos.Num(); ++i) {
		ClientSetInventoryItem(i, ItemInfos[i]);
	}
}

void UCNInventoryManager::ClientSetInventoryItem_Implementation(int SlotPos, const FCNItemInfo& ItemInfo)
{
	BPSetInventoryItem(SlotPos, ItemInfo);
}

void UCNInventoryManager::ClientSetContainerItem_Implementation(int SlotPos, const FCNItemInfo& ItemInfo)
{
	BPSetContainerItem(SlotPos, ItemInfo);
}

void UCNInventoryManager::ClientSetEquipmentItem_Implementation(int SlotPos, const FCNItemInfo& ItemInfo)
{
	BPSetEquipmentItem(SlotPos, ItemInfo);
}

void UCNInventoryManager::AddItem(UCNInventoryComponent * InventoryComp, int SlotPos, const FCNItemInfo& ItemInfo)
{
	InventoryComp->SetItem(SlotPos, ItemInfo);

	// Inventory is target
	if (InventoryComp == PlayerInventory) {
		ClientSetInventoryItem(SlotPos, ItemInfo);
	}
	// Equipment is target
	else if (InventoryComp == PlayerEquipment) {
		ClientSetEquipmentItem(SlotPos, ItemInfo);
	}
	// Container is target
	else {

		// Check
		if (!CurrentContainer) {
			return;
		}

		// Update every viewer
		for (auto x : CurrentContainer->PlayerStates) {
			auto OwnerController = x->GetOwner();
			if (auto Player = Cast<ACNPlayerController>(OwnerController)) {
				// Close container UI
				Player->InventoryManager->ClientSetContainerItem(SlotPos, ItemInfo);
			}
		}
	}
}

void UCNInventoryManager::ClientRemoveInventoryItem_Implementation(int SlotPos)
{
	BPRemoveInventoryItem(SlotPos);
}

void UCNInventoryManager::ClientRemoveContainerItem_Implementation(int SlotPos)
{
	BPRemoveContainerItem(SlotPos);
}

void UCNInventoryManager::ClientRemoveEquipmentItem_Implementation(int SlotPos)
{
	BPRemoveEquipmentItem(SlotPos);
}

void UCNInventoryManager::RemoveItem(UCNInventoryComponent * InventoryComp, int SlotPos)
{
	InventoryComp->ClearItem(SlotPos);

	// Inventory is target
	if (InventoryComp == PlayerInventory) {
		ClientRemoveInventoryItem(SlotPos);
	}
	// Equipment is target
	else if (InventoryComp == PlayerEquipment) {
		ClientRemoveEquipmentItem(SlotPos);
	}
	// Container is target
	else {

		// Check
		if (!CurrentContainer) {
			return;
		}

		// Update every viewer
		for (auto x : CurrentContainer->PlayerStates) {
			auto OwnerController = x->GetOwner();
			if (auto Player = Cast<ACNPlayerController>(OwnerController)) {
				// Close container UI
				Player->InventoryManager->ClientRemoveContainerItem(SlotPos);
			}
		}
	}
}

void UCNInventoryManager::MoveItem(UCNInventoryComponent* FromInventoryComp, int FromSlotPos,
	UCNInventoryComponent* ToInventoryComp, int ToSlotPos)
{
	// Check valid handle
	if (!FromInventoryComp || !ToInventoryComp) {
		return;
	}

	// Check same slot
	if (FromInventoryComp == ToInventoryComp && FromSlotPos == ToSlotPos) {
		return;
	}

	FCNItemInfo ItemInfo = FromInventoryComp->GetItem(FromSlotPos);
	FCNItemInfo ToItemInfo = ToInventoryComp->GetItem(ToSlotPos);

	auto Item = UCNObjectFactoryLib::FindItemByID(
		UGameplayStatics::GetGameState(GetWorld()),
		ItemInfo.Index);

	// Target exists
	if (ToItemInfo.Index.IsValid()) {

		// Same item, stack it
		if (ItemInfo.Index == ToItemInfo.Index) {

			if (Item->GetStackable()) {
				AddItemAmount(ToInventoryComp, ToSlotPos, ItemInfo.Amount);
				RemoveItem(FromInventoryComp, FromSlotPos);
				return;
			}
		}

		// Different items, swap item
		AddItem(ToInventoryComp, ToSlotPos, ItemInfo);
		AddItem(FromInventoryComp, FromSlotPos, ToItemInfo);
		return;
	}
	// Target is non-existent
	else {

		// Stackable, try stack item first
		if (Item->GetStackable() && FromInventoryComp != ToInventoryComp) {
			if (FindAndMoveToStack(FromInventoryComp, FromSlotPos,
				ToInventoryComp, ItemInfo)) {
				return;
			}
		}

		AddItem(ToInventoryComp, ToSlotPos, ItemInfo);
		RemoveItem(FromInventoryComp, FromSlotPos);
		return;
	}
}

void UCNInventoryManager::DropItem(UCNInventoryComponent * InventoryComp, int SlotPos)
{
	
}

bool UCNInventoryManager::HaveItem(UCNInventoryComponent * InventoryComp, FString Name)
{
	return false;
}

void UCNInventoryManager::UseContainerItem(int SlotPos)
{
	
}

int UCNInventoryManager::GetEquipmentSlotPos(const FCNItemInfo& ItemInfo)
{
	auto Item = UCNObjectFactoryLib::FindItemByID(
		UGameplayStatics::GetGameState(GetWorld()),
		ItemInfo.Index);

	return int(Item->GetCurBaseAttri().EquipmentType) - 1;
}

//

void UCNInventoryManager::UseInventoryItem(int SlotPos)
{
	FCNItemInfo ItemInfo = PlayerInventory->GetItem(SlotPos);

	auto Item = UCNObjectFactoryLib::FindItemByID(
		UGameplayStatics::GetGameState(GetWorld()),
		ItemInfo.Index);

	auto Type = Item->GetCurBaseAttri().ItemType;
	switch (Type) {
	case ECNItemType::EQUIPMENT:
		AddItem(PlayerEquipment, GetEquipmentSlotPos(ItemInfo), ItemInfo);
		RemoveItem(PlayerInventory, SlotPos);
		break;
	case ECNItemType::CONSUMABLE:
		break;
	}
}

void UCNInventoryManager::UseEquipmentItem()
{
	// FCNItemInfo ItemInfo = CurrentContainer->InventoryComponent->GetItem(SlotPos);
}
