// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CNInventoryComponent.h"
#include "CNAttriBase.h"
#include "CNEquipsComponent.generated.h"

struct FCNItemInfo;
class UCNItem;

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CNBASE_API UCNEquipsComponent : public UCNInventoryComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCNEquipsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const FCNItemInfo& GetEquipment(int EquipType);

	virtual void SetItem(int Pos, const FCNItemInfo& Info) override;

	virtual void ClearItem(int Pos) override;

private:
	/**
	 * Equipments array starts from 0 but Equipment type starts from 1
	 */
	int EquipTypeToArrayIndex(int EquipType);
};
