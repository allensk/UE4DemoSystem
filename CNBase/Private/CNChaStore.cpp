// Fill out your copyright notice in the Description page of Project Settings.


#include "CNChaStore.h"
#include "Paths.h"

#include "CNAttriBase.h"
#include "SQLiteDatabase.h"
#include "CNUtility.h"
#include "CNDBConnection.h"

FCNChaStore::FCNChaStore() :
	Db(*GetDbRef())
{
	TableName = TEXT("ChaBaseStore");
}

FCNChaStore::~FCNChaStore()
{
	
}

bool FCNChaStore::LoadAllData()
{
	return true;
}

FString FCNChaStore::GetDescription(int ID)
{
	return FString();
}

FString FCNChaStore::GetName(int ID)
{
	return FString();
}

FString FCNChaStore::GetAssetPath(int ID)
{
	return FString();
}

TSharedPtr<FCNChaBase> FCNChaStore::FindBase(FString Name)
{
	// SQL

	return nullptr;
}