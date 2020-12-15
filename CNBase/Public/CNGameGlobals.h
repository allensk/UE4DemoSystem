// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CNGameLog.h"

// Collision type
#define COLLISION_WEAPON_COLLISION				ECC_GameTraceChannel1

// Surface type constants
#define PHYSICAL_MATERIAL_FLESHDEFAULT			SurfaceType1
#define PHYSICAL_MATERIAL_FLESH_VULNERABLE		SurfaceType2

// String table used for localization
extern CNBASE_API FName GCodeSTable;
extern CNBASE_API FName GUISTable;
extern CNBASE_API FName GConverSTable;
extern CNBASE_API FName GItemSTable;