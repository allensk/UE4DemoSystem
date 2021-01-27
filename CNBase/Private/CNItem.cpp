// Fill out your copyright notice in the Description page of Project Settings.


#include "CNItem.h"

#include "Paths.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameState.h"
#include "Engine/World.h"
#include "Internationalization/StringTableRegistry.h"
#include "Net/UnrealNetwork.h"
#include "Net/DataChannel.h"

#include "CNItemStore.h"
#include "CNGameState.h"
#include "CNGameLog.h"
#include "CNTypeLib.h"
#include "CNGameGlobals.h"

#pragma optimize( "", off )

UCNItem::UCNItem()
{	
	// Amount = 1;
	TestInt = 10;
	ItemStore = new FCNItemStore();
}

UCNItem::~UCNItem()
{
	delete ItemStore;
}

void UCNItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME_CONDITION(UCNItem, Amount, ELifetimeCondition::COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UCNItem, CurBaseAttri, ELifetimeCondition::COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UCNItem, Name, ELifetimeCondition::COND_OwnerOnly);
	// DOREPLIFETIME_CONDITION(UCNItem, Level, ELifetimeCondition::COND_OwnerOnly);
}

void UCNItem::SetBasicData(FString BaseName, ECNObjectLevel InLevel)
{
	BaseAttri = ItemStore->FindBase(BaseName);
	BaseAttri.Index.Level = (int)InLevel;
	if (BaseAttri.Index.ID) {
		CurBaseAttri = BaseAttri;
	}
}

void UCNItem::SetBasicDataByID(int ID, ECNObjectLevel InLevel)
{
	BaseAttri = ItemStore->FindBase(ID);
	BaseAttri.Index.Level = (int)InLevel;
	if (BaseAttri.Index.ID) {
		CurBaseAttri = BaseAttri;
	}
}

FString UCNItem::GetIconPath() const
{
	return ItemStore->FindIconPath(CurBaseAttri.Index.ID);
}

bool UCNItem::GetStackable() const
{
	return ItemStore->FindStackable(CurBaseAttri.Index.ID);
}

FText UCNItem::GetDescription() const
{
	FString Key = ItemStore->FindDescription(CurBaseAttri.Index.ID);
	return FText::FromStringTable(GItemSTable, Key);
}
	
FText UCNItem::GetTypeText() const
{
	FString Key = ItemStore->FindType(CurBaseAttri.Index.ID);

	FText Out;
	FText::FindText(TEXT("Item"), Key, Out);
	return Out;
}

FText UCNItem::GetEquipsTypeText() const
{
	FString Key = ItemStore->FindEquipType(CurBaseAttri.Index.ID);
	FText Out;
	FText::FindText(TEXT("Item"), Key, Out);
	return Out;
}

FString UCNItem::GetBasicName() const
{
	return ItemStore->FindName(CurBaseAttri.Index.ID);
}

FText UCNItem::GetName() const
{
	auto Key1 = UCNTypeLib::GetLevelSTKey((ECNObjectLevel)CurBaseAttri.Index.Level);
	auto Key2 = ItemStore->FindDisplayName(CurBaseAttri.Index.ID);
	auto t1 = FText::FromStringTable(GItemSTable, Key1.ToString());
	auto t2 = FText::FromStringTable(GItemSTable, Key2);
	auto s = t1.ToString() + TEXT(" ") + t2.ToString();
	return FText::FromString(s);
}

FCNConsumableEffect UCNItem::GetConsumableEffect() const
{
	return ItemStore->GetConsumableEffect(CurBaseAttri.Index.ID);
}

#pragma optimize( "", on )