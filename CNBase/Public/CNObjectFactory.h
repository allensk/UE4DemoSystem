// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CNAttriBase.h"
#include "Runtime/Core/Public/HAL/ThreadingBase.h"
#include "CNObjectFactory.generated.h"

class UCNItem;
class UCNCha;

UCLASS(BlueprintType)
class CNBASE_API ACNObjectFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACNObjectFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCNItem* FindItem(FCNObjectIndex Index);

	UCNCha* FindCharacter(FCNObjectIndex Index);

private:
	
	UPROPERTY()
	TMap<FCNObjectIndex, UObject*> Objects;

	FCriticalSection Mutex;
};
