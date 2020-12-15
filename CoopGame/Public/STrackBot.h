// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STrackBot.generated.h"

class UStaticMeshComponent;
class USHealthComponent;
class USphereComponent;

UCLASS()
class COOPGAME_API ASTrackBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTrackBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = Component)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Component)
	USHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Component)
	USphereComponent* SphereComponent;

	// Move

	FVector NextPoint;

	FVector GetPawnNextPoint();

	UPROPERTY(EditDefaultsOnly, Category = Move)
		float DistanceRequire;

	UPROPERTY(EditDefaultsOnly, Category = Move)
		float MoveForce;

	UPROPERTY(EditDefaultsOnly, Category = Move)
		bool bUseVelocityChange;

	// Health handler

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastHealthChangeEffect();

	UFUNCTION()
	void OnHealthChange(USHealthComponent* OwnerHealthComponent, float Health, float HealthDelta,
			const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/// Dynamic Material to pulse
	UMaterialInstanceDynamic* HurtDynamicMaterial;

	//

	UFUNCTION(NetMulticast, Reliable)
	void MulticastDestroySelfEffect();

	void DestroySelf();

	/**
	* Cause Damage on itself
	*/
	void DamageSelf();
	
	FTimerHandle TimeHanldeDamageSelf;

	bool StartDamageSelf;

	//

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	UParticleSystem* ExplosiveSphere;
	
	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	UParticleSystem* ExplosiveEffect;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float ExplosiveRadius;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	float ExplosiveDamage;

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	USoundBase* ExplosiveWarningSound;
	
	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	USoundBase* ExplosiveSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void Destroyed() override;
};
