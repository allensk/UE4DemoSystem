// Fill out your copyright notice in the Description page of Project Settings.


#include "CNObjectLib.h"

#include "Engine/Texture2D.h"

#pragma optimize( "", off )

template <typename ObjectClass>
static FORCEINLINE ObjectClass* LoadObjectFromPath(const FString& Path)
{
	if (!Path.Len()) return NULL;
	return Cast<ObjectClass>(StaticLoadObject(ObjectClass::StaticClass(), NULL, *Path));
}

//Get Path
FString UCNObjectLib::GetObjectPath(const UObject* Obj)
{
	FString Path;

	if (!Obj) {
		return Path;
	}

	//~
	FStringAssetReference ThePath = FStringAssetReference(Obj);

	if (!ThePath.IsValid()) return Path;

	//The Class FString Name For This Object
	FString Str = Obj->GetClass()->GetDescription();

	Str += "'";
	Str += ThePath.ToString();
	Str += "'";

	return FString(*Str);
}

UTexture2D* UCNObjectLib::LoadTexture2DFromPath(const FString& Path)
{
	return LoadObjectFromPath<UTexture2D>(Path);
}

#pragma optimize( "", on)
