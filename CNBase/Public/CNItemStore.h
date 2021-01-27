// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "UObject/NoExportTypes.h"
// #include "CNItemStore.generated.h"

#include "CNDBConnection.h"

struct FCNItemBase;
struct FCNConsumableEffect;
class FSQLiteDatabase;

/**
 * 
 */

class CNBASE_API FCNItemStore : public FCNDBConnection
{

public:
	FCNItemStore();
	~FCNItemStore() override;

	bool LoadAllData();

	/**
	 * @Return indexed name
	 */
	FString FindName(int ID) const;

	/**
	 * @Return Name meaningful to player
	 */
	FString FindDisplayName(int ID) const;

	/**
	 * @Return base attribute description
	 */
	FString FindDescription(int ID) const;

	/**
	 * Find item base attributes
	 */
	FCNItemBase FindBase(FString Name) const;

	/**
	 * Find item base attributes
	 */
	FCNItemBase FindBase(int ID) const;

	/**
	 * @Return return asset relative path to game content
	 */
	FString FindAssetPath(int ID) const;

	/**
	 * Find icon path
	 */
	FString FindIconPath(int ID) const;

	/**
	 * Find Item type
	 */
	FString FindType(int ID) const;

	/**
	 * Find Equipment Type
	 */
	FString FindEquipType(int ID) const;

	/**
	 * Find If Item is stockable.
	 */
	bool FindStackable(int ID) const;

	/**
	 * Get default icon
	 */
	bool GetDefaultIconPath(FString Type, FString& IconPath) const;

	/**
	 * Get all consumable effects
	 */
	FCNConsumableEffect GetConsumableEffect(int ID) const;

protected:
	
	bool IsIdValid(int ID) const;
	
private:

	FSQLiteDatabase& Db;
	FString ConsumableEffectTable;
};
