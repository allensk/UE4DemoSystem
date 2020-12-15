// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Net/UnrealNetwork.h"

#include "Misc/FeedbackContext.h"

#include "CoopGame.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	BulletSpread = 1.0f;
	BaseDamage = 20.0f;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASWeapon::FireInternal()
{
	AActor* WeaponOwner = GetOwner();
	if (WeaponOwner) {

		FVector EyeLocation;
		FRotator EyeRotation;
		WeaponOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		FRotator ShootRotation = FMath::VRandCone(EyeRotation.Vector(),
			FMath::DegreesToRadians(BulletSpread)).Rotation();
		FVector EyeEnd = EyeLocation + (ShootRotation.GetNormalized().Vector() * 10000);
		HitTrace.TraceEnd = EyeEnd;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(WeaponOwner);
		Params.AddIgnoredActor(this);
		Params.bTraceComplex = true;
		Params.bReturnPhysicalMaterial = true;

		FHitResult HitResult = {};
		if (GetWorld()->LineTraceSingleByChannel(HitResult,
			EyeLocation,
			EyeEnd,
			COLLISION_WEAPON_COLLISION,
			Params)) {

			EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
			
			if (Role == ROLE_Authority) {
				
				// Determine surface time and increase flesh damage
				float ShootDamage = 0.0;
				UParticleSystem* Effect = nullptr;
				switch (SurfaceType) {
				case PHYSICAL_MATERIAL_FLESHDEFAULT:
				case PHYSICAL_MATERIAL_FLESH_VULNERABLE:
					Effect = FleshImpactEffect;
					ShootDamage = BaseDamage * 2;
					break;
				default:
					Effect = DefaultImpactEffect;
					ShootDamage = BaseDamage;
				}
				
				// Impose damage
				TSubclassOf<UDamageType> DamageType;
				UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),
					ShootDamage,
					HitResult.Normal,
					HitResult,
					WeaponOwner->GetInstigatorController(),
					this,
					DamageType);

				// Play effect
				HitTrace.SurfaceType = SurfaceType;
				HitTrace.TraceEnd = HitResult.ImpactPoint;
				HitTrace.Normal = HitResult.Normal;
				
				PlayImpactEffect(HitTrace.TraceEnd, HitTrace.SurfaceType, HitTrace.Normal);
				PlayEffect(HitTrace.TraceEnd);
			}
		}

		if (CVarShowDebugMesh.GetValueOnGameThread() == 1) {
			DrawDebugLine(GetWorld(), EyeLocation, EyeEnd, FColor::White, false, 1.0f, 0, 1.0f);
		}
	}
}

void ASWeapon::ServerFire_Implementation()
{
	FireInternal();
}

bool ASWeapon::ServerFire_Validate()
{
	return true;
}

void ASWeapon::Fire()
{
	ServerFire();
}

void ASWeapon::PlayEffect(FVector TraceEnd)
{
	if (MuzzleEffect) {
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect,
			MeshComp,
			MuzzleSocketName);
	}

	if (TraceEffect) {

		auto MuzzleLoc = MeshComp->GetSocketLocation(MuzzleSocketName);

		UParticleSystemComponent* Comp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			TraceEffect,
			MuzzleLoc);

		Comp->SetVectorParameter("Target", TraceEnd);
	}

	ACharacter* Cha = Cast<ACharacter>(GetOwner());
	if (Cha) {
		APlayerController* Controller = Cast<APlayerController>(Cha->GetController());
		if (Controller) {
			Controller->ClientPlayCameraShake(CameraShake);
		}
	}
}

void ASWeapon::PlayImpactEffect(FVector Point, EPhysicalSurface SurfaceType, FVector Normal)
{
	UParticleSystem* Effect = nullptr;
	switch (SurfaceType) {
	case PHYSICAL_MATERIAL_FLESHDEFAULT:
	case PHYSICAL_MATERIAL_FLESH_VULNERABLE:
		Effect = FleshImpactEffect;
		break;
	default:
		Effect = DefaultImpactEffect;
	}

	if (Effect) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			Effect,
			Point,
			Normal.Rotation(),
			true);
	}
}

void ASWeapon::OnRep_ReceiveHitTrance()
{
	PlayEffect(HitTrace.TraceEnd);
	PlayImpactEffect(HitTrace.TraceEnd, HitTrace.SurfaceType, HitTrace.Normal);
}

void ASWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASWeapon, HitTrace);
}