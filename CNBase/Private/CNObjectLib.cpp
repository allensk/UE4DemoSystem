// Fill out your copyright notice in the Description page of Project Settings.


#include "CNObjectLib.h"

#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "CNGameLog.h"
#include "FileManager.h"

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

UStaticMesh* UCNObjectLib::LoadStaticMeshFromPath(const FString& Path)
{
	return LoadObjectFromPath<UStaticMesh>(Path);
}

TArray<UStaticMesh*> UCNObjectLib::GetDirectoryStaticMesh(FString ContentRelativePath)
{
	TArray<UStaticMesh*> Array;
	TArray<FString> Files;

	IFileManager::Get().FindFiles(Files, *FPaths::ProjectContentDir().Append(ContentRelativePath));

	TArray<FString> FilteredFiles;
	for (auto x : Files) {
		if (x.Find(TEXT(".uasset")) != INDEX_NONE) {
			FilteredFiles.Push(x);
		}
	}

	UE_LOG(CNLog, Warning, TEXT("Asset Number: %d"), FilteredFiles.Num());

	for (auto x : FilteredFiles) {

		int Index = 0;
		if (x.FindChar(TEXT('.'), Index)) {
			FString BaseName = x.Left(Index);
			FString ObjectPath = 
			FString::Printf(TEXT("StaticMesh'/Game/%s/%s.%s'"), *ContentRelativePath, *BaseName, *BaseName);
		
			UStaticMesh* Mesh = LoadStaticMeshFromPath(ObjectPath);
			UE_LOG(CNLog, Warning, TEXT("Mesh Path:%s"), *ObjectPath);
			UE_LOG(CNLog, Warning, TEXT("Mesh pointer: %p"), Mesh);

			if (Mesh) {
				Array.Add(Mesh);
			}

		}
	}
	
	return Array;
}

#pragma optimize( "", on)
