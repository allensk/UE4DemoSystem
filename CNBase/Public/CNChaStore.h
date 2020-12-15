// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "UObject/NoExportTypes.h"
// #include "CNChaStore.generated.h"
#include "CNDBConnection.h"


struct FCNChaBase;
class FSQLiteDatabase;

/**
 * 
 */

class CNBASE_API FCNChaStore : public FCNDBConnection
{
public:
	FCNChaStore();
	~FCNChaStore() override;

	bool LoadAllData();

	/**
	 * @Return base attribute description
	 */
	FString GetDescription(int ID);

	/**
	 * @Return base attribute name
	 */
	FString GetName(int ID);

	/**
	 * @Return return asset relative path to game content
	 */
	FString GetAssetPath(int ID);

	TSharedPtr<FCNChaBase> FindBase(FString Name);
	
private:
	TMap<int, TSharedPtr<FCNChaBase>> Map;
	FSQLiteDatabase& Db;
};
