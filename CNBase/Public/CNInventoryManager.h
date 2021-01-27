// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CNContainerActor.h"
#include "CNInventoryManager.generated.h"

class UCNInventoryComponent;
class UCNEquipsComponent;
struct FCNItemInfo;

/**
 * All functions should be executed on server, or called by playercontroller except
 * having obvious Client prefix.
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CNBASE_API UCNInventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCNInventoryManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Blueprintcallable)
	void BPInitialize(UCNInventoryComponent* InventoryComp,
		UCNEquipsComponent* EquipsComp);

	//

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPOpenContainer(ACNContainerActor* Container, const TArray<FCNItemInfo>& ItemInfos);
	
	UFUNCTION(Client, Reliable)
	void ClientOpenContainer(ACNContainerActor* Container, const TArray<FCNItemInfo>& ItemInfos);

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPCloseContainer(ACNContainerActor* Container);

	UFUNCTION(Client, Reliable)
	void ClientCloseContainer(ACNContainerActor* Container);

	void OpenContainer(ACNContainerActor* Container);

	void UseContainer(ACNContainerActor* Container);

	void CloseContainer();

	/**
	 *
	 */
	void MoveItemInInventory(int FromSlotPos, int ToSlotPos);

	/**
	 * 
	 */
	void MoveItemInContainer(int FromSlotPos, int ToSlotPos);

	void TakeContainerItem(int FromContainerSlotPos, int ToInventorySlotPos);

	void DepositContainerItem(int FromInventorySlotPos, int ToContainerSlotPos);

	/**
	 *
	 */
	void UnEquipItem(int FromEquipmentSlotPos, int ToInventorySlotPos);

	// Stack

	void AddItemAmount(UCNInventoryComponent* InventoryComp, int SlotPos, int Amount);

	void ReduceItemAmount(UCNInventoryComponent* InventoryComp, int SlotPos, int Amount);

	bool FindAndMoveToStack(UCNInventoryComponent* FromInventoryComp, int FromSlotPos,
		UCNInventoryComponent* ToInventoryComp, const FCNItemInfo& ItemInfo);

	/**
	 * Must be in some container
	 */
	void SplitItem(UCNInventoryComponent* InventoryComp, int FromSlotPos, int ToSlotPos, int Amount);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void BPClearInventory();
	
	UFUNCTION(Client, Reliable)
	void ClientClearInventory();

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPClearContainer();

	UFUNCTION(Client, Reliable)
	void ClientClearContainer();

	// Inventory
	UFUNCTION(Blueprintcallable)
	void RefreshInventory();

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPSetInventoryItem(int SlotPos, const FCNItemInfo& ItemInfo);

	UFUNCTION(Client, Reliable)
	void ClientSetInventoryItem(int SlotPos, const FCNItemInfo& ItemInfo);

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPSetContainerItem(int SlotPos, const FCNItemInfo& ItemInfo);

	UFUNCTION(Client, Reliable)
	void ClientSetContainerItem(int SlotPos, const FCNItemInfo& ItemInfo);

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment)
	void BPSetEquipmentItem(int SlotPos, const FCNItemInfo& ItemInfo);

	UFUNCTION(Client, Reliable)
	void ClientSetEquipmentItem(int SlotPos, const FCNItemInfo& ItemInfo);

	// Add Item to Inventory
	void AddItem(UCNInventoryComponent* InventoryComp, int SlotPos, const FCNItemInfo& Item);

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPRemoveInventoryItem(int SlotPos);

	UFUNCTION(Client, Reliable)
	void ClientRemoveInventoryItem(int SlotPos);

	UFUNCTION(BlueprintImplementableEvent, Category = Container)
	void BPRemoveContainerItem(int SlotPos);

	UFUNCTION(Client, Reliable)
	void ClientRemoveContainerItem(int SlotPos);

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment)
	void BPRemoveEquipmentItem(int SlotPos);

	UFUNCTION(Client, Reliable)
	void ClientRemoveEquipmentItem(int SlotPos);

	void RemoveItem(UCNInventoryComponent* InventoryComp, int SlotPos);

	/**
	 * Move Item in Inventory, Key function
	 */
	void MoveItem(UCNInventoryComponent* FromInventoryComp, int FromSlotPos,
		UCNInventoryComponent* ToInventoryComp, int ToSlotPos);

	// Drop Item to World
	void DropItem(UCNInventoryComponent* InventoryComp, int SlotPos);

	// Check If item is in inventory
	bool HaveItem(UCNInventoryComponent* InventoryComp, FString Name);

	// Use
	void UseContainerItem(int SlotPos);

	/**
	 * @param ItemInfo passed equipment assured ItemInfo
	 */
	int GetEquipmentSlotPos(const FCNItemInfo& ItemInfo);
	
	void UseInventoryItem(int SlotPos);

	void UseEquipmentItem();

protected:
	void ChangItemAmount(UCNInventoryComponent* InventoryComp, int SlotPos, int Amount);

public:

	/**
	 * Be the same pointer in PlayerController
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCNInventoryComponent* PlayerInventory;

	/**
	 * Be the same pointer in PlayerController
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCNEquipsComponent* PlayerEquipment;

	ACNContainerActor* CurrentContainer;
};
