// Fill out your copyright notice in the Description page of Project Settings.


#include "CNInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Net/DataChannel.h"
#include "Engine/ActorChannel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"

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
}


// Called every frame
void UCNInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}

void UCNInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UE_LOG(CNLog, Verbose, TEXT("UCNInventoryComponent::InitializeComponent"));
}

bool UCNInventoryComponent::IsInventoryFull()
{
	return false;
}

void UCNInventoryComponent::LoadItems()
{
	TestAddConsumableToInitData();
	TestAddEquipmentsToInitData();
	LoadInitData();
}

void UCNInventoryComponent::LoadInitData()
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

	// Clear
	InitDatas.Empty();
}

void UCNInventoryComponent::TestAddConsumableToInitData()
{
	FCNObjectInitData Data{ TEXT("Black Bread") };
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Chicken Leg");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Chicken Leg Set");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Dark Egg");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("White Egg");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Sang");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Sausage");
	InitDatas.Add(Data);
}

void UCNInventoryComponent::TestAddEquipmentsToInitData()
{
	FCNObjectInitData Data{ TEXT("Sword_1") };
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Shield_1");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Sword_2");
	InitDatas.Add(Data);
	Data.BaseName = TEXT("Shield_2");
	InitDatas.Add(Data);
}

bool UCNInventoryComponent::FindItem(const FCNItemInfo& ItemInfo, int& Pos)
{
	if (ItemInfos.Find(ItemInfo, Pos)) {
		return true;
	}

	return false;
}

const FCNItemInfo& UCNInventoryComponent::GetItem(int Pos) const
{
	if (!ItemInfos.IsValidIndex(Pos)) {
		static FCNItemInfo Info;
		return Info;
	}

	return ItemInfos[Pos];
}

void UCNInventoryComponent::SetItem(int Pos, const FCNItemInfo& Info)
{	
	// Refer to KismetArrayLibrary GenArraySet
	if (!ItemInfos.IsValidIndex(Pos)  && (Pos >= 0)) {
		ItemInfos.SetNumZeroed(Pos + 1, true);
	}

	if (ItemInfos.IsValidIndex(Pos)) {
		ItemInfos[Pos] = Info;
	}
}

void UCNInventoryComponent::ClearItem(int Pos)
{
	if (ItemInfos.IsValidIndex(Pos)) {
		ItemInfos[Pos] = FCNItemInfo();
	}
}

int UCNInventoryComponent::GetItemsCount()
{
	return ItemInfos.Num();
}

bool UCNInventoryComponent::GetEmptyPos(int& Pos)
{
	for (int i = 0; i < ItemInfos.Num(); ++i) {
		
		// Invalid Item
		if (!ItemInfos[i].Index.IsValid()) {
			Pos = i;
			return true;
		}
	}

	return false;
}

void UCNInventoryComponent::ChangeItemNum(UCNItem* Item, int Num)
{
	// Skip nullptr and no-change
	if (!Item || !Num) {
		return;
	}
}