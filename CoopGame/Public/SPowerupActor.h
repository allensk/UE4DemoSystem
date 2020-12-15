// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"

UCLASS()
class COOPGAME_API ASPowerupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Powerups)
	float PowerupIntervals;

	UPROPERTY(EditDefaultsOnly, Category = Powerups)
	int TotalNumOfTicks;

	UFUNCTION()
	void OnTickPowerup();

	int TickProcessed;

	FTimerHandle TimeHandlePowerupTick;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivatePowerup();

	UFUNCTION(BlueprintImplementableEvent, Category = Powerups)
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = Powerups)
	void OnPowerupTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = Powerups)
	void OnExpired();
};
