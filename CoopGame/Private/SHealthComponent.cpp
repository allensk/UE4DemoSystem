// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "EngineGlobals.h"
#include "GameFramework/Controller.h"

#include "CoopGame.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;

	// ...

	DefaultHealth = 100.0f;
	Health = DefaultHealth;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority) {
		AActor* Owner = GetOwner();
		if (Owner) {
			Owner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::AnyDamageHandle);
		}
	}
}

// Called every frame
void USHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USHealthComponent::MulticastHealthChange_Implementation(float NewHealth)
{
	Health = NewHealth;

	OnHealthChangedNetMulti.Broadcast(this, Health);
}

void USHealthComponent::AnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0) {
		return;
	}

	float NewHealth = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	if (Health == NewHealth) {
		return;
	}

	Health = NewHealth;
	MulticastHealthChange(Health);
	
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
	
	if (DamagedActor) {
		UE_LOG(GameLog, Verbose, TEXT("%s hitted(health) by %f."), *DamagedActor->GetName(), Health);
	}
}

void USHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME(USHealthComponent, Health);
}

void USHealthComponent::Heal(int Amount)
{
	if (GetOwnerRole() != ROLE_Authority) {
		return;
	}

	if (Amount < 0 || Health == 0) {
		return;
	}

	Health = FMath::Clamp(Health + Amount, 0.0f, DefaultHealth);
	MulticastHealthChange(Health);
	OnHealthChanged.Broadcast(this, Health, Amount, nullptr, nullptr, nullptr);

	if (GetOwner()) {
		UE_LOG(GameLog, Verbose, TEXT("%s healed(health) %f."), *GetOwner()->GetName(), Health);
	}
}