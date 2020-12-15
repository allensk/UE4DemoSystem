// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Logging/LogMacros.h"

CNBASE_API DECLARE_LOG_CATEGORY_EXTERN(CNLog, Log, All);

// Console command
extern CNBASE_API TAutoConsoleVariable<int32> CVarShowDebugMesh;

extern CNBASE_API TAutoConsoleVariable<int32> CVarShowDebugText;

#include "Engine/Engine.h"
#define GPrintText(text, ...) \
		if (GEngine && CVarShowDebugText.GetValueOnGameThread() == 1) \
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, FString::Printf(text, ##__VA_ARGS__))
