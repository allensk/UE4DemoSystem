// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CNAttriBase.h"
#include "CNInventoryComponent.generated.h"

class UCNItem;

/**
 * FOnAddOrRemoveItemSignature type
 */
UENUM(BlueprintType)
enum class EItemChangeNumEvent : uint8
{
	ADD,
	REMOVE
};

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddOrRemoveItemSignature, bool, Add, UCNItem*, Item);

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CNBASE_API UCNInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCNInventoryComponent();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	void LoadItems();

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnAddOrRemoveItemSignature OnAddOrRemoveItem;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	UFUNCTION(Client, Reliable)
	void ClientSetItemNum(UCNItem* Item, int Num);

	UFUNCTION(Client, Reliable)
	void ClientRemoveItem(UCNItem* Item);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerChangeItemNum(UCNItem* Item, int Num);

	UFUNCTION(BlueprintCallable)
	void ChangeItemNum(UCNItem* Item, int Num);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	virtual void ServerUseItem(int Slot);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Items")
	TArray<FCNObjectInitData> InitDatas;

	/**
	 * Replicate, initialized on server
	 */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Items")
	TArray<FCNItemInfo> ItemInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	int ItemMaxAmount;
};
