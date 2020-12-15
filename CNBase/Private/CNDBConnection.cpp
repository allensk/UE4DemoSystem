// Fill out your copyright notice in the Description page of Project Settings.


#include "CNDBConnection.h"
#include "SQLiteDatabase.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"

#include <ctime>

#include "CNUtility.h"
#include "CNGameLog.h"

FSQLiteDatabase* FCNDBConnection::Db{ nullptr };
std::atomic<int> FCNDBConnection::count{ 0 };
FString FCNDBConnection::TmpFile;

FCNDBConnection::FCNDBConnection()
{
	// Allocate resource
	if (!Db) {

		// Just for development test purpose.
		std::time_t t = std::time(0);
		TmpFile = FCNUtility::GetContentDir().Append("Data/Tmp").Append(FString::FromInt((int32)t));
		FPlatformFileManager::Get().GetPlatformFile().CopyFile(*TmpFile,
			*FCNUtility::GetDBFilePath(),
			EPlatformFileRead::AllowWrite
		);

		Db = new FSQLiteDatabase();
		auto DBPath = FCNUtility::GetDBFilePath();
		// ReadOnly flagg is useless
		// Db->Open(*DBPath, ESQLiteDatabaseOpenMode::ReadOnly);
		Db->Open(*TmpFile, ESQLiteDatabaseOpenMode::ReadOnly);
		ensure(Db->IsValid());
	}
	
	++count;
}

FCNDBConnection::~FCNDBConnection()
{
	--count;

	// Clear resource
	if (!count && Db) {
		Db->Close();
		delete Db;
		Db = nullptr;
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*TmpFile);
		TmpFile.Empty();
	}
}

template<typename T>
bool FCNDBConnection::QueryValue(FString& Query, T& Value) const
{
	if (Db->IsValid()) {
		FSQLitePreparedStatement State(*Db, *Query);

		// Aready bound
		if (!State.IsValid()) {
			UE_LOG(LogTemp, Log, TEXT("Db State is invalid."));
			return false;
		}

		// Return a row
		if (State.Step() == ESQLitePreparedStatementStepResult::Row) {
			if (State.GetColumnValueByIndex(0, Value)) {
				return true;
			}
		}
		return false;
	}

	return false;
}

template bool FCNDBConnection::QueryValue(FString&, FString&) const;

// 

template<typename T>
bool FCNDBConnection::InnerGetValueOfID(int ID, FString ColumnName, T& Value) const
{
	FString ConditionalQuery = FString::Printf(TEXT("SELECT %s FROM %s WHERE id = %d;"),
		*ColumnName, *TableName, ID);
	return QueryValue(ConditionalQuery, Value);
}

int FCNDBConnection::GetObjectID(const FString& Name)
{
	int ID = 0;
	FString StateString = FString::Printf(
		TEXT("SELECT id FROM %s WHERE name == '%s';"), *TableName, *Name);
	QueryValue(StateString, ID);
	return ID;
}

bool FCNDBConnection::GetValueOfID(int ID, FString ColumnName, FString& Value) const
{
	return InnerGetValueOfID(ID, ColumnName, Value);
}

bool FCNDBConnection::GetValueOfID(int ID, FString ColumnName, double& Value) const
{
	return InnerGetValueOfID(ID, ColumnName, Value);
}

bool FCNDBConnection::GetValueOfID(int ID, FString ColumnName, int& Value) const
{
	return InnerGetValueOfID(ID, ColumnName, Value);
}

