// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CNInventoryComponent.h"
#include "CNEquipsComponent.generated.h"

class UCNItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipSignature, int, Slot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CNBASE_API UCNEquipsComponent : public UCNInventoryComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCNEquipsComponent();

	UPROPERTY(BlueprintAssignable, Category = Events)
	FEquipSignature OnEquipItem;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Text();

	/**
	 * 
	 */
	/*UFUNCTION(BlueprintCallable)
	bool IsItemEquipped(int Slot);*/

	/*UFUNCTION(Client, Reliable)
	void ClientItemEquipped(int Slot, ItemInfo);*/

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void ServerEquipItem(int Slot);
	
	/**
	 * Pass a pointer reference, Change pointer to another item
	 * Exchange inventory item with equipment item
	 */
	//UFUNCTION(BlueprintCallable)
	//void EquipItem(UCNItem* Item, bool bEquip);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Items")
	TArray<FCNItemInfo> EquipInfos;
};
