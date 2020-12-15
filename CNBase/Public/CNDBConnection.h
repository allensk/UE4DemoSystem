// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <atomic>

class FSQLiteDatabase;

/**
 * 
 */
class CNBASE_API FCNDBConnection
{
public:
	FCNDBConnection();
	virtual ~FCNDBConnection();

	FSQLiteDatabase* GetDbRef() const { return Db; } 

	/**
	 * SQLite Quick function
	 */
	template<typename T>
	bool QueryValue(FString& Query, T& Value) const;

	/**
	 * Query the ID of an object
	 * @Return 0 for failure otherwise success
 	 */
	int GetObjectID(const FString& Name);

	bool GetValueOfID(int ID, FString ColumnName, FString& Value) const;
	bool GetValueOfID(int ID, FString ColumnName, double& Value) const;
	bool GetValueOfID(int ID, FString ColumnName, int& Value) const;

private:

	/**
	 * SQLite Quick function
	 * With ID passed
	 */
	template<typename T>
	bool InnerGetValueOfID(int ID, FString ColumnName, T& Value) const;
	
protected:
	FString TableName{ TEXT("None") };

private:
	static FSQLiteDatabase*  Db;
	static std::atomic<int> count;
	static FString TmpFile;
};
