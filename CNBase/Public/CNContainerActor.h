// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CNUsableActor.h"
#include "CNInventoryComponent.h"
#include "GameFramework/PlayerState.h"
#include "CNContainerActor.generated.h"

/**
 * 
 */
UCLASS()
class CNBASE_API ACNContainerActor : public ACNUsableActor
{
	GENERATED_BODY()

public:

	ACNContainerActor();

	/**
	 * Server Function
	 */
	virtual bool Use_Implementation(APlayerController* PlayerController) override;

	UFUNCTION()
	bool Loot();

	UFUNCTION(BlueprintCallable)
	bool CanStoreItems() { return bCanStore; }

	UFUNCTION(BlueprintCallable)
	UCNInventoryComponent* GetInventory() { return InventoryComponent; }

	/*UFUNCTION(BlueprintCallable)
	void InitializeInventory();*/

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UCNInventoryComponent* InventoryComponent;

	// Manager players who open container concurrently
	TArray<APlayerState*> PlayerStates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Container)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Container)
	int SlotsPerRow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Container)
	int SlotsNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Container)
	bool bCanStore;
};
