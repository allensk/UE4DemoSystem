// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CNAttriBase.h"
#include "CNInventoryComponent.generated.h"

class UCNItem;

/**
 *
 */
UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CNBASE_API UCNInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCNInventoryComponent();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	bool IsInventoryFull();

	/**
	 * For server initialization
	 */
	void LoadItems();

	/**
	 * Test purpose
	 */
	void TestAddConsumableToInitData();
	void TestAddEquipmentsToInitData();
	
	/**
	 * Load Initialization items
	 */
	void LoadInitData();

	/**
	 * @param if found pos contain position value
	 * @return true if found
	 */
	bool FindItem(const FCNItemInfo& ItemInfo, int& Pos);

	const FCNItemInfo& GetItem(int Pos) const;

	virtual void SetItem(int Pos, const FCNItemInfo& Info);

	virtual void ClearItem(int Pos);
	
	int GetItemsCount();

	/**
	 * @param Pos store valid position
	 * @return true if successfully find an empty position, 
	 * false for no empty position.
	 */
	bool GetEmptyPos(int& Pos);

	// Amount ceiling
	int GetItemMaxAmount() { return ItemMaxAmount; }

	const TArray<FCNItemInfo>& GetItems() const { return ItemInfos; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	void ChangeItemNum(UCNItem* Item, int Num);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Items")
	TArray<FCNObjectInitData> InitDatas;

	/**
	 * Replicate, initialized on server
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Items")
	TArray<FCNItemInfo> ItemInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	int ItemMaxAmount;
};
