// Fill out your copyright notice in the Description page of Project Settings.


#include "STrackBot.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Public/TimerManager.h"
#include "GameFramework/Character.h"

#include "CoopGame.h"
#include "SHealthComponent.h"
#include "SCharacter.h"
#include "CNActorLib.h"


// Sets default values
ASTrackBot::ASTrackBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCanEverAffectNavigation(false);
	RootComponent = StaticMesh;

	HealthComponent = CreateDefaultSubobject<USHealthComponent>("HealthComp");
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollisionComp");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetSphereRadius(150);
	SphereComponent->SetupAttachment(RootComponent);
	
	DistanceRequire = 100.0f;
	MoveForce = 1000.0f;
	bUseVelocityChange = true;

	ExplosiveDamage = 40;
	ExplosiveRadius = 200;

	SetReplicates(true);
	SetReplicateMovement(true);

	int a = 0;
	a++;
}

// Called when the game starts or when spawned
void ASTrackBot::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority) {
		HealthComponent->OnHealthChanged.AddDynamic(this, &ASTrackBot::OnHealthChange);
	}
}

// Called every frame
void ASTrackBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Role == ROLE_Authority) {
		
		NextPoint = GetPawnNextPoint();
		FVector Loc = GetActorLocation();

		if ((Loc - NextPoint).Size() < DistanceRequire) {
			return;
		}

		// Move to next point
		FVector Direct = NextPoint - Loc;
		Direct.Normalize();
		Direct *= MoveForce;
		StaticMesh->AddForce(Direct, NAME_None, bUseVelocityChange);
	}
}

// Called to bind functionality to input
void ASTrackBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FVector ASTrackBot::GetPawnNextPoint()
{
	if (Role != ROLE_Authority)
		return GetActorLocation();

	TArray<AActor*> Actors;
	auto Iterator = GetWorld()->GetPawnIterator();
	for (; Iterator; ++Iterator) {
		Actors.Push(Cast<AActor>(*Iterator));
	}

	AActor* NearestActor = UCNActorLib::GetNearestActor(this, Actors, "Player");
	ASCharacter* Player = Cast<ASCharacter>(NearestActor);
	if (Player) {
		
		UNavigationPath* Path = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(),
			GetActorLocation(),
			Player);

		// 0 is start point itself
		if (Path && (Path->PathPoints.Num() > 1)) {
			return Path->PathPoints[1];
		}
	}

	return GetActorLocation();
}

void ASTrackBot::Destroyed()
{
	Super::Destroyed();
}

void ASTrackBot::MulticastDestroySelfEffect_Implementation()
{
	if (IsValid(this)) {

		if (ExplosiveSphere) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				ExplosiveSphere,
				GetActorLocation());
		}

		// Produce explosive sign
		if (ExplosiveEffect) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				ExplosiveEffect,
				GetActorLocation());
		}

		UGameplayStatics::SpawnSoundAttached(ExplosiveSound, RootComponent);

		if (CVarShowDebugMesh.GetValueOnGameThread() == 1) {
			DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosiveRadius, 16, FColor::Red, false, 5.0f, 0, 2);
		}

		GetWorldTimerManager().ClearTimer(TimeHanldeDamageSelf);
	}
}

void ASTrackBot::DestroySelf()
{
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	// Make damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(),
		ExplosiveDamage,
		GetActorLocation(),
		ExplosiveRadius,
		nullptr,
		IgnoredActors,
		this,
		GetInstigatorController(),
		true);

	MulticastDestroySelfEffect();

	//SetLifeSpan(3);
	Destroy();
}

void ASTrackBot::MulticastHealthChangeEffect_Implementation()
{
	if (!HurtDynamicMaterial) {
		HurtDynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0,
			StaticMesh->GetMaterial(0));
	}

	if (HurtDynamicMaterial) {
		HurtDynamicMaterial->SetScalarParameterValue("LastTimeDamageTaken", GetWorld()->TimeSeconds);
	}
}

void ASTrackBot::OnHealthChange(USHealthComponent* OwnerHealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	MulticastHealthChangeEffect();

	if (Health == 0.0f) {
		DestroySelf();
	}
}

void ASTrackBot::DamageSelf()
{
	UGameplayStatics::ApplyDamage(this,
		40,
		GetInstigatorController(),
		this,
		nullptr); // Damage type
}

void ASTrackBot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(GameLog, Verbose, TEXT("NotifyActorBeginOverlap %d"), (int)Role);

	if (!StartDamageSelf) {
		// If a pawn overlapped this actor
		ACharacter* Cha = Cast<ACharacter>(OtherActor);
		if (Cha) {

			StartDamageSelf = true;

			GetWorldTimerManager().ClearTimer(TimeHanldeDamageSelf);
			GetWorldTimerManager().SetTimer(TimeHanldeDamageSelf, this, &ASTrackBot::DamageSelf, 0.5, true);
			
			UGameplayStatics::SpawnSoundAttached(ExplosiveWarningSound, RootComponent);
		}
	}
}