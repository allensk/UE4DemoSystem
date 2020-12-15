// Fill out your copyright notice in the Description page of Project Settings.


#include "CNItemStore.h"
#include "Paths.h"
#include "SQLiteDatabase.h"
#include "SQLitePreparedStatement.h"

#include "CNAttriBase.h"
#include "CNUtility.h"
#include "CNGameLog.h"
#include "CNDBConnection.h"

#include "Engine/Engine.h"

namespace {
	
/**
* Convert human readable text into enumeration
*/
ECNItemType ItemTypeStringToEnum(const FString& Type)
{
	if (Type == TEXT("Equipment")) {
		return ECNItemType::EQUIPMENT;
	}
	else if (Type == TEXT("Consumable")) {
		return ECNItemType::CONSUMABLE;
	}
	else if (Type == TEXT("Currency")) {
		return ECNItemType::CURRENCY;
	}
	else if (Type == TEXT("Miscellaneous")) {
		return ECNItemType::MISCELLANEOUS;
	}

	return ECNItemType();
}

/**
 * Convert human readable text into enumeration
 */
ECNEquipmentType EquipsTypeStringToEnum(const FString& Type)
{
	if (Type == TEXT("Head")) {
		return ECNEquipmentType::HEAD;
	}
	else if (Type == TEXT("Weapon")) {
		return ECNEquipmentType::WEAPON;
	}
	else if (Type == TEXT("Body")) {
		return ECNEquipmentType::BODY;
	}
	else if (Type == TEXT("Boot")) {
		return ECNEquipmentType::BOOT;
	}
	else if (Type == TEXT("Artifact")) {
		return ECNEquipmentType::ARTIFACT;
	}

	return ECNEquipmentType::NONE;
}

};

FCNItemStore::FCNItemStore() :
	Db(*GetDbRef())
{
	TableName = TEXT("ItemBaseStore");
}

FCNItemStore::~FCNItemStore()
{

}

bool FCNItemStore::IsIdValid(int ID) const
{
	return GetValueOfID(ID, TEXT("id"), ID);
}

bool FCNItemStore::LoadAllData()
{
	UE_LOG(CNLog, Log, TEXT("Db LoadAllData begin."));

	if (Db.IsValid()) {
		return false;
	}
		
	FString StateString = TEXT("SELECT id, name, CivilAb, MilitaryAb, ForceAb, PoliticalAb, ArtAb FROM ItemBaseStore;");
	FSQLitePreparedStatement State(Db, *StateString);
	if (!State.IsValid()) 		{
		return false;
	} 

	auto Res = ESQLitePreparedStatementStepResult::Row;
	while (Res == ESQLitePreparedStatementStepResult::Row) {
		Res = State.Step();
		if (Res == ESQLitePreparedStatementStepResult::Row) {
				
			auto ItemBase = MakeShared<FCNItemBase>();
			State.GetColumnValueByName(TEXT("id"), ItemBase->Index.ID);
			State.GetColumnValueByName(TEXT("CivilAb"), ItemBase->CivilAb);
			State.GetColumnValueByName(TEXT("MilitaryAb"), ItemBase->MilitaryAb);
			State.GetColumnValueByName(TEXT("ForceAb"), ItemBase->ForceAb);
			State.GetColumnValueByName(TEXT("PoliticalAb"), ItemBase->PoliticalAb);
			State.GetColumnValueByName(TEXT("ArtAb"), ItemBase->ArtAb);
		}
	}

	UE_LOG(CNLog, Log, TEXT("Db LoadAllData end."));

	return true;
}

FString FCNItemStore::FindDescription(int ID) const
{
	FString Ret;
	GetValueOfID(ID, TEXT("desc"), Ret);
	return Ret;
}

FString FCNItemStore::FindName(int ID) const
{
	FString Ret;
	GetValueOfID(ID, TEXT("name"), Ret);
	return Ret;
}

FString FCNItemStore::FindAssetPath(int ID) const
{
	return FString();
}

FCNItemBase FCNItemStore::FindBase(FString Name) const
{
	FString StateString = FString::Printf(
		TEXT("SELECT id, name, CivilAb, MilitaryAb, ForceAb, PoliticalAb, ArtAb, ItemType, EquipmentType"
			" FROM ItemBaseStore WHERE name == '%s';"), *Name);
	
	FSQLitePreparedStatement State(Db, *StateString);
	if (State.IsValid()) {
		// Return a row
		if (State.Step() == ESQLitePreparedStatementStepResult::Row) {
			
			//
			FCNItemBase ItemBase;
			State.GetColumnValueByName(TEXT("id"), ItemBase.Index.ID);
			State.GetColumnValueByName(TEXT("CivilAb"), ItemBase.CivilAb);
			State.GetColumnValueByName(TEXT("MilitaryAb"), ItemBase.MilitaryAb);
			State.GetColumnValueByName(TEXT("ForceAb"), ItemBase.ForceAb);
			State.GetColumnValueByName(TEXT("PoliticalAb"), ItemBase.PoliticalAb);
			State.GetColumnValueByName(TEXT("ArtAb"), ItemBase.ArtAb);

			//
			FString Tmp;
			State.GetColumnValueByName(TEXT("ItemType"), Tmp);
			ItemBase.ItemType = ItemTypeStringToEnum(Tmp);
			State.GetColumnValueByName(TEXT("EquipmentType"), Tmp);
			ItemBase.EquipmentType = EquipsTypeStringToEnum(Tmp);
			
			return ItemBase;
		}
	}

	return FCNItemBase();
}

FCNItemBase FCNItemStore::FindBase(int ID) const
{
	return FindBase(FindName(ID));
}

FString FCNItemStore::FindType(int ID) const
{
	FString Ret;
	GetValueOfID(ID, TEXT("ItemType"), Ret);
	return Ret;
}

FString FCNItemStore::FindEquipType(int ID) const
{
	FString Ret;
	GetValueOfID(ID, TEXT("EquipmentType"), Ret);
	return Ret;
}

bool FCNItemStore::GetDefaultIconPath(FString Type, FString& IconPath) const
{
	FString StateString = FString::Printf(TEXT("SELECT IconPath FROM DefaultIcons WHERE name = '%s';"), *Type);
	return QueryValue(StateString, IconPath);
}

FString FCNItemStore::FindIconPath(int ID) const
{
	FString Ret;
	// Find IconPath in db
	GetValueOfID(ID, TEXT("IconPath"), Ret);
	if (!Ret.Len()) {
		FString Type;
		Type = FindType(ID);
		// Filter next
		if (Type == TEXT("Equipment")) {
			Type = FindEquipType(ID);
		}

		// Roll back to default icon
		GetDefaultIconPath(Type, Ret);
	}
	
	return Ret;
}