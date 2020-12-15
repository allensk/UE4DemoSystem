// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CNAttriBase.generated.h"

//
UENUM(BlueprintType)
enum class ECNObjectLevel : uint8
{
	COMMON = 1,
	FIRST = 1,
	
	UNCOMMON = 2,
	SECOND = 2,
	
	RARE = 3,
	THIRD = 3,
	
	EPIC = 4,
	FORTH = 4,
	
	LEGENDARY = 5,
	FIFTH = 5,
};

ENUM_CLASS_FLAGS(ECNObjectLevel)

//
UENUM(BlueprintType)
enum class ECNAbilityType : uint8
{
	NONE = 0,
	CIVIL = 1,
	MILITARY = 2,
	COMMAND = 3,
	POLITICAL = 4,
	ART = 5,
};

ENUM_CLASS_FLAGS(ECNAbilityType)

//
UENUM(BlueprintType)
enum class ECNItemType : uint8
{
	NONE = 0,
	EQUIPMENT,
	CONSUMABLE,
	CURRENCY,
	MISCELLANEOUS
};

ENUM_CLASS_FLAGS(ECNItemType)

//
UENUM(BlueprintType)
enum class ECNEquipmentType : uint8
{
	NONE = 0,
	HEAD,
	WEAPON,
	BODY,
	BOOT,
	ARTIFACT,
};

ENUM_CLASS_FLAGS(ECNEquipmentType)

//
UENUM(BlueprintType)
enum class ECNChaType : uint8
{
	NONE,
	PLAYER,
	MONSTER,
	NPC
};

ENUM_CLASS_FLAGS(ECNChaType)


////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FCNObjectIndex
{
	GENERATED_USTRUCT_BODY()

public:
	FCNObjectIndex() = default;

	bool operator<(const FCNObjectIndex& Index) const {
		if (this->ID != Index.ID)
			return this->ID < Index.ID;

		return this->Level < Index.Level;
	}

	bool operator==(const FCNObjectIndex& Index) const
	{
		return this->ID == Index.ID && this->Level == Index.Level;
	}

	FORCEINLINE friend uint32 GetTypeHash(const FCNObjectIndex& Index) 
	{ 
		uint32 Hash = 0;
		Hash = ::GetTypeHash(Index.ID);
		Hash = ::HashCombine(Hash, ::GetTypeHash(Index.Level));
		return Hash;
	}

	UPROPERTY(BlueprintReadOnly)
	int ID{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int Level{ 0 };
};

USTRUCT(BlueprintType)
struct FCNObjectBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCNObjectBase() = default;
	
	UPROPERTY(BlueprintReadOnly)
	int CivilAb{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int MilitaryAb{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int PoliticalAb{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int ForceAb{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int ArtAb{ 0 };

	/**
	 * Index in temporary store (for example in CNItemStore).
	 * The same as db index
	 */
	UPROPERTY()
	FCNObjectIndex Index;
};

USTRUCT(BlueprintType)
struct FCNItemBase : public FCNObjectBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCNItemBase() = default;

	UPROPERTY(BlueprintReadOnly)
	ECNItemType		 ItemType{ ECNItemType::NONE };

	UPROPERTY(BlueprintReadOnly)
	ECNEquipmentType EquipmentType{ ECNEquipmentType::NONE };
};


USTRUCT(BlueprintType)
struct FCNChaBase : public FCNObjectBase
{
	GENERATED_USTRUCT_BODY()
public:	
	FCNChaBase() = default;

	UPROPERTY(BlueprintReadOnly)
	ECNChaType		ChaType{ ECNChaType::NONE };

	UPROPERTY(BlueprintReadOnly)
	int				UnderstandingAb{ 0 };

	UPROPERTY(BlueprintReadOnly)
	int64			Health{ 1000 };
};

////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FCNObjectInitData
{
	GENERATED_USTRUCT_BODY()
public:
	FCNObjectInitData() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString			 BaseName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ECNObjectLevel   Level { ECNObjectLevel::FIRST };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Amount{ 1 };
};

/**
 * Transient struct
 */
USTRUCT(BlueprintType)
struct FCNItemInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	FCNObjectIndex Index;

	UPROPERTY(BlueprintReadWrite)
	int Amount{ 1 };
};