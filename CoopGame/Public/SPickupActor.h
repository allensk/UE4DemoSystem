// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPickupActor.generated.h"

class USphereComponent;
class UDecalComponent;
class ASPowerupActor;

UCLASS()
class COOPGAME_API ASPickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UDecalComponent* DecalComponent;

	// 
	UPROPERTY(EditInstanceOnly, Category = Pickups)
	TSubclassOf<ASPowerupActor> PowerupClass;

	UPROPERTY(EditInstanceOnly, Category = Pickups)
	float CoolDownPowerup;

	FTimerHandle TimeHandleCoolDown;
	
	UPROPERTY(Replicated)
	ASPowerupActor* PowerupActor;

	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
