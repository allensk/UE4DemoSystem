// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FSQLiteDatabase;

/**
 * 
 */
class CNBASE_API FCNUtility
{
public:
	static FCNUtility& GetInstance();
	static FString& GetDBFilePath();
	static FString& GetContentDir();
	
private:
	FCNUtility();
	~FCNUtility();
};
