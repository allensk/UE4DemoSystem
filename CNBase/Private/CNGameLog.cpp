// Fill out your copyright notice in the Description page of Project Settings.


#include "CNGameLog.h"
// Log

DEFINE_LOG_CATEGORY(CNLog);

// Console variables

TAutoConsoleVariable<int32> CVarShowDebugMesh(TEXT("G.Mesh"),
	0,
	TEXT("Show debug sphere"),
	ECVF_Scalability | ECVF_RenderThreadSafe);


TAutoConsoleVariable<int32> CVarShowDebugText(TEXT("G.Text"),
	1,
	TEXT("Show debug text"),
	ECVF_Scalability | ECVF_RenderThreadSafe);