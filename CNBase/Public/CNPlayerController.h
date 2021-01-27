// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CNInventoryManager.h"
#include "CNEquipsComponent.h"
#include "CNPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CNBASE_API ACNPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACNPlayerController();
	virtual ~ACNPlayerController() override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Blueprintcallable)
	AActor* GetUsableActor();

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerUseActor();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = Container)
	void ServerUseContainer(ACNContainerActor* Container);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerCloseContainer();

	/**
	 * Inventory action
	 */
	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerUseInventoryItem(int SlotPos);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerMoveInventoryItem(int FromSlotPos, int ToSlotPos);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerTakeContainerItem(int FromSlotPos, int ToSlotPos);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerDepositContainerItem(int FromSlotPos, int ToSlotPos);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerUnEquipItem(int FromSlotPos, int ToSlotPos = -1);

	/**
	 * Container action
	 */
	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerUseContainerItem(int SlotPos);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerMoveContainerItem(int FromSlotPos, int ToSlotPos);

	UFUNCTION(Blueprintcallable, Server, Reliable, WithValidation, Category = Action)
	void ServerLoadItems();

	void LoadItems();

public:

	UPROPERTY(BlueprintReadWrite, Category = Components)
	UCNEquipsComponent* EquipmentComponent;

	UPROPERTY(BlueprintReadWrite, Category = Components)
	UCNInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = Components)
	UCNInventoryManager* InventoryManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxUseDistance;

	// Camera spring arm length redefined
	float SpringArmLength; 
};
