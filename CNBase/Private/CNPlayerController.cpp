// Fill out your copyright notice in the Description page of Project Settings.


#include "CNPlayerController.h"
#include "CNGameLog.h"
#include "CNUsableActorInterface.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"

ACNPlayerController::ACNPlayerController()
{
	EquipmentComponent = CreateDefaultSubobject<UCNEquipsComponent>("EquipmentComponent");
	InventoryComponent = CreateDefaultSubobject<UCNInventoryComponent>("InventoryComponent");
	
	FAttachmentTransformRules Rules(FAttachmentTransformRules::KeepRelativeTransform);
	EquipmentComponent->AttachToComponent(RootComponent, Rules);
	InventoryComponent->AttachToComponent(RootComponent, Rules);

	MaxUseDistance = 200.0;
	SpringArmLength = 100.0;
}

ACNPlayerController::~ACNPlayerController()
{

}

void ACNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(CNLog, Warning, TEXT("Begin Play, Role:%d"), (int)Role);

	if (IsLocalController()) {
		ServerLoadItems();
	}
}

void ACNPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACNPlayerController, InventoryManager,
		ELifetimeCondition::COND_InitialOrOwner);
}

AActor* ACNPlayerController::GetUsableActor()
{
	FVector EyeLocation;
	FRotator EyeRotation;

	FVector TraceBegin = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = PlayerCameraManager->GetCameraRotation().Vector() *
		(MaxUseDistance + SpringArmLength) + TraceBegin;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor((AActor*)GetCharacter());
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = true;
	
	FHitResult HitResult = {};
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		TraceBegin,
		TraceEnd,
		ECC_Visibility,
		Params))
	{
		ICNUsableActorInterface* Usable = Cast<ICNUsableActorInterface>(HitResult.GetActor());
		if (Usable) {
			return HitResult.GetActor();
		}
	}

	return nullptr;
}

void ACNPlayerController::ServerUseActor_Implementation()
{
	AActor* Actor = GetUsableActor();
	ICNUsableActorInterface* Usable = Cast<ICNUsableActorInterface>(Actor);
	if (Usable) {
		Usable->Execute_Use(Actor, this);
	}
}

bool ACNPlayerController::ServerUseActor_Validate()
{
	return true;
}

void ACNPlayerController::ServerUseContainer_Implementation(ACNContainerActor* Container)
{
	InventoryManager->UseContainer(Container);
}

bool ACNPlayerController::ServerUseContainer_Validate(ACNContainerActor* Container)
{
	return true;
}

void ACNPlayerController::ServerCloseContainer_Implementation()
{
	InventoryManager->CloseContainer();
}

bool ACNPlayerController::ServerCloseContainer_Validate()
{
	return true;
}

void ACNPlayerController::ServerUseInventoryItem_Implementation(int SlotPos)
{
	InventoryManager->UseInventoryItem(SlotPos);
}

bool ACNPlayerController::ServerUseInventoryItem_Validate(int SlotPos)
{
	return true;
}

void ACNPlayerController::ServerMoveInventoryItem_Implementation(int FromSlotPos, int ToSlotPos)
{
	InventoryManager->MoveItemInInventory(FromSlotPos, ToSlotPos);
}

bool ACNPlayerController::ServerMoveInventoryItem_Validate(int FromSlotPos, int ToSlotPos)
{
	return true;
}

void ACNPlayerController::ServerTakeContainerItem_Implementation(int FromSlotPos, int ToSlotPos)
{
	InventoryManager->TakeContainerItem(FromSlotPos, ToSlotPos);
}

bool ACNPlayerController::ServerTakeContainerItem_Validate(int FromSlotPos, int ToSlotPos)
{
	return true;
}

void ACNPlayerController::ServerDepositContainerItem_Implementation(int FromSlotPos, int ToSlotPos)
{
	InventoryManager->DepositContainerItem(FromSlotPos, ToSlotPos);
}

bool ACNPlayerController::ServerDepositContainerItem_Validate(int FromSlotPos, int ToSlotPos)
{
	return true;
}

void ACNPlayerController::ServerUnEquipItem_Implementation(int FromSlotPos, int ToSlotPos)
{
	InventoryManager->UnEquipItem(ToSlotPos, ToSlotPos);
}

bool ACNPlayerController::ServerUnEquipItem_Validate(int FromSlotPos, int ToSlotPos)
{
	return true;
}

void ACNPlayerController::ServerUseContainerItem_Implementation(int SlotPos)
{
	InventoryManager->UseContainerItem(SlotPos);
}

bool ACNPlayerController::ServerUseContainerItem_Validate(int SlotPos)
{
	return true;
}

void ACNPlayerController::ServerMoveContainerItem_Implementation(int FromSlotPos, int ToSlotPos)
{
	InventoryManager->MoveItemInContainer(FromSlotPos, ToSlotPos);
}

bool ACNPlayerController::ServerMoveContainerItem_Validate(int FromSlotPos, int ToSlotPos)
{
	return true;
}

void ACNPlayerController::ServerLoadItems_Implementation()
{
	LoadItems();
	InventoryManager->RefreshInventory();
}

bool ACNPlayerController::ServerLoadItems_Validate()
{
	return true;
}

void ACNPlayerController::LoadItems()
{
	InventoryComponent->LoadItems();
}
