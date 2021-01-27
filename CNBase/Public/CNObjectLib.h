// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNObjectLib.generated.h"

class UTexture2D;
class UStaticMesh;

/**
 * 
 */
UCLASS()
class CNBASE_API UCNObjectLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Get the reference path to a object
	 */
	UFUNCTION(BlueprintCallable, Category = ObjectLib)
	static FString GetObjectPath(const UObject* Obj);

	/**
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category = ObjectLib)
	static UTexture2D* LoadTexture2DFromPath(const FString& Path);

	UFUNCTION(BlueprintCallable, Category = ObjectLib)
	static UStaticMesh* LoadStaticMeshFromPath(const FString& Path);

	/**
	 * Only enumerate .uasset files
	 */
	UFUNCTION(BlueprintCallable, Category = ObjectLib)
	static TArray<UStaticMesh*> GetDirectoryStaticMesh(FString ContentRelativePath);
};
