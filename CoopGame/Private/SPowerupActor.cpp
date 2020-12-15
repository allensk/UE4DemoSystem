// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"
#include "Engine/Public/TimerManager.h"

// Sets default values
ASPowerupActor::ASPowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupIntervals = 0;
	TotalNumOfTicks = 0;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASPowerupActor::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ASPowerupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASPowerupActor::OnTickPowerup()
{
	++TickProcessed;

	OnPowerupTicked();

	if (TotalNumOfTicks <= TickProcessed) {
		
		GetWorldTimerManager().ClearTimer(TimeHandlePowerupTick);

		OnExpired();
	}
}

void ASPowerupActor::ActivatePowerup()
{
	OnActivated();

	if (PowerupIntervals > 0) {
		GetWorldTimerManager().SetTimer(TimeHandlePowerupTick, this, &ASPowerupActor::OnTickPowerup, PowerupIntervals, true);
	}
	else {
		OnTickPowerup();
	}


}
