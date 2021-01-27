// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSpawnSubordiatesComponent.generated.h"

class UEnvQuery;
struct FEnvQueryResult;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOPGAME_API UPSpawnSubordiatesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPSpawnSubordiatesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Call this function to spawn subordinates,
	 * Spawned actor's owner is set to this component's owner,
	 * It will check authority.
	 */
	UFUNCTION(Blueprintcallable)
	void SpawnSubordinates();

private:
	void EQSQueryFinished(TSharedPtr<FEnvQueryResult> Result);

public:

	// Return points
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	UEnvQuery* SpawnEQS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Spawn)
	TSubclassOf<AActor> SubordinateClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Spawn)
	int DesiredSpawnNum;

private:

};
