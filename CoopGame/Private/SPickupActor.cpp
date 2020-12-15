// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupActor.h"

#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/Public/TimerManager.h"
#include "Net/UnrealNetwork.h"

#include "CoopGame.h"
#include "SPowerupActor.h"

// Sets default values
ASPickupActor::ASPickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetSphereRadius(50);
	RootComponent = SphereComponent;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	DecalComponent->DecalSize = FVector(50, 50, 50);
	DecalComponent->SetRelativeRotation(FRotator(90, 0, 0));
	DecalComponent->SetupAttachment(RootComponent);

	CoolDownPowerup = 10.0f;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASPickupActor::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

// Called every frame
void ASPickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASPickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (PowerupActor) {
		PowerupActor->ActivatePowerup();
		PowerupActor = nullptr;

		GetWorldTimerManager().SetTimer(TimeHandleCoolDown, this, &ASPickupActor::Spawn, CoolDownPowerup);
	}
}

void ASPickupActor::Spawn()
{
	if (Role != ROLE_Authority)
		return;

	if (!PowerupClass) {
		UE_LOG(GameLog, Warning, TEXT("Powerup Class is unspecified."));
		return;
	}

	if (!PowerupActor) {

		FActorSpawnParameters Params = {};
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PowerupActor = GetWorld()->SpawnActor<ASPowerupActor>(PowerupClass, GetTransform(), Params);
		if (PowerupActor) {

		}

		return;
	}
}

void ASPickupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPickupActor, PowerupActor);
}