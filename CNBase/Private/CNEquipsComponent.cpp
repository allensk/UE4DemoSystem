// Fill out your copyright notice in the Description page of Project Settings.


#include "CNEquipsComponent.h"

#include "Kismet/GameplayStatics.h"

#include "CNItem.h"
#include "CNObjectFactoryLib.h"

// Sets default values for this component's properties
UCNEquipsComponent::UCNEquipsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UCNEquipsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCNEquipsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCNEquipsComponent::Text()
{
}

//bool UCNEquipsComponent::IsItemEquipped(int Slot)
//{
//	EquipInfos.RangeCheck
//
//	/*for (auto& Elem : EquippedItems) {
//		if (Elem.Value == Item) {
//			return true;
//		}
//	}*/
//
//	return false;
//}

//void UCNEquipsComponent::ClientEquipItem_Implementation(UCNItem* Item, bool bEquip)
//{
//	OnEquipOrUnEquipItem.Broadcast(bEquip, Item);
//}

void UCNEquipsComponent::ServerEquipItem_Implementation(int Slot)
{
	auto& Info = ItemInfos[Slot];
	auto* Item = UCNObjectFactoryLib::FindItemByID(UGameplayStatics::GetGameState(GetWorld()),
		Info.Index);
	if (Item) {
		if (Item->GetCurBaseAttri().ItemType == ECNItemType::EQUIPMENT) {
			ItemInfos.RemoveAt(Slot, 1, false);
			EquipInfos.Insert(Info, (int)Item->GetCurBaseAttri().EquipmentType);
		}
		else {
			
		}
	}
}

bool UCNEquipsComponent::ServerEquipItem_Validate(int Slot)
{

	return true;
}

//void UCNEquipsComponent::EquipItem(UCNItem* SlotItemAddress, bool bEquip)
//{
//	ServerEquipItem(SlotItemAddress, bEquip);
//
//	//SlotItemAddress->name
//}

void UCNEquipsComponent::InitializeComponent()
{
	Super::InitializeComponent();
}