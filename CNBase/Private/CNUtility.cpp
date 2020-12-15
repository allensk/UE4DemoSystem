// Fill out your copyright notice in the Description page of Project Settings.


#include "CNUtility.h"
#include "Paths.h"
#include "SQLiteDatabase.h"
#include "SQLitePreparedStatement.h"

FCNUtility::FCNUtility()
{
}

FCNUtility::~FCNUtility()
{
}

FCNUtility& FCNUtility::GetInstance()
{
	static FCNUtility Utility;
	return Utility;
}

FString& FCNUtility::GetDBFilePath()
{
	static FString DbPath;
	static FString CttDir = FPaths::ProjectContentDir();

	if (DbPath.Len()) {
		return DbPath;
	}

	DbPath = CttDir + TEXT("Data/CNGame.db");
	return DbPath;
}

FString & FCNUtility::GetContentDir()
{
	static FString CttDir = FPaths::ProjectContentDir();
	if (CttDir.Len()) {
		return CttDir;
	}
	
	return CttDir;
}
