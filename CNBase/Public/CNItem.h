// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CNAttriBase.h"
#include "CNItem.generated.h"

class FCNItemStore;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), BlueprintType)
class CNBASE_API UCNItem : public UObject
{
	GENERATED_BODY()

public:
	UCNItem();
	~UCNItem() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool IsSupportedForNetworking() const override { return true; };

	/**
	 * Have to be called to load certain data
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetBasicData(FString BaseName, ECNObjectLevel InLevel);

	/**
	 * Have to be called to load certain data
	 */
	virtual void SetBasicDataByID(int ID, ECNObjectLevel InLevel);

	/** */
	UFUNCTION(BlueprintCallable)
	FString GetIconPath() const;

	/** */
	UFUNCTION(BlueprintCallable)
	bool GetStackable() const;

	/** */
	UFUNCTION(BlueprintCallable)
	FText GetDescription() const;

	/** */
	UFUNCTION(BlueprintCallable)
	FText GetTypeText() const;

	/** */
	UFUNCTION(BlueprintCallable)
	FText GetEquipsTypeText() const;

	/** */
	UFUNCTION(BlueprintCallable)
	ECNObjectLevel GetLevel() const { return (ECNObjectLevel)CurBaseAttri.Index.Level; }

	/** */
	UFUNCTION(BlueprintCallable)
	FString GetBasicName() const;

	/** */
	UFUNCTION(BlueprintCallable)
	FText GetName() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Custom")
	int TestInt;

	const FCNItemBase& GetCurBaseAttri() const { return CurBaseAttri; }

	int GetAmount() const { return Amount; }
	void SetAmount(int Num) { Amount = Num; }

protected:

	FCNItemBase BaseAttri;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Custom")
	int	Amount;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Custom")
	FCNItemBase CurBaseAttri;

	UPROPERTY(Replicated)
	FText Name;

	FCNItemStore* ItemStore{ nullptr };
};
