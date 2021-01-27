// Fill out your copyright notice in the Description page of Project Settings.


#include "CNEquipsComponent.h"

#include "Kismet/GameplayStatics.h"

#include "CNItem.h"
#include "CNObjectFactoryLib.h"
#include "..\Public\CNEquipsComponent.h"

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

void UCNEquipsComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called every frame
void UCNEquipsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const FCNItemInfo& UCNEquipsComponent::GetEquipment(int EquipType)
{
	return GetItem(EquipTypeToArrayIndex(EquipType));
}

void UCNEquipsComponent::SetItem(int Pos, const FCNItemInfo & Info)
{
	Super::SetItem(Pos, Info);
}

void UCNEquipsComponent::ClearItem(int Pos)
{
	Super::ClearItem(Pos);
}

int UCNEquipsComponent::EquipTypeToArrayIndex(int EquipType)
{
	return EquipType - 1;
}

/*switch (Type) {
case ECNEquipmentType::HEAD:
	break;
case ECNEquipmentType::BODY:
	break;
case ECNEquipmentType::BOOT:
	break;
case ECNEquipmentType::WEAPON:
	break;
case ECNEquipmentType::ARTIFACT:
	break;
}*/