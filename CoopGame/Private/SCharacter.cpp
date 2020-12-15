// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <EngineGlobals.h>
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Public/TimerManager.h"
#include "AIController.h"

#include "AISystem.h"
#include "Perception/AIPerceptionComponent.h"

#include "SWeapon.h"
#include "CoopGame.h"
#include "SHealthComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON_COLLISION, ECR_Block);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	Weapon = nullptr;

	ZoomedFov = 65.0f;
	ZoomInterpSpeed = 20.0f;
	FireRate = 600;
	WeaponSocket = "WeaponSocket";
	bDied = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = CameraComponent->FieldOfView;

	if (Role == ROLE_Authority) {
		FTransform TransForm = {};
		FActorSpawnParameters Params = {};
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Weapon = GetWorld()->SpawnActor<ASWeapon>(WeaponClass, TransForm, Params);
		if (Weapon) {
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}

		HealthComponent->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Fov = WantZoom ? ZoomedFov : DefaultFOV;
	Fov = FMath::FInterpTo(CameraComponent->FieldOfView, Fov, DeltaTime, ZoomInterpSpeed);

	CameraComponent->SetFieldOfView(Fov);
}


void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASCharacter::BeginCrouch()
{
	Crouch();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Crouch"));
}

void ASCharacter::EndCrouch()
{
	UnCrouch();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Crouch"));
}

void ASCharacter::BeginZoom()
{
	WantZoom = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Zoom"));
}

void ASCharacter::EndZoom()
{
	WantZoom = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Zoom"));
}

void ASCharacter::Jump()
{
	Super::Jump();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Jump"));
}

void ASCharacter::Fire()
{
	if (!bDied && Weapon) {
		Weapon->Fire();
	}
}

void ASCharacter::StartFire()
{
	GetWorldTimerManager().SetTimer(TimeHandleFire, this, &ASCharacter::Fire, 60 / FireRate, true);
}

void ASCharacter::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimeHandleFire);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Lookup", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASCharacter::EndZoom);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASCharacter::StopFire);

	// PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);
}

void ASCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	Super::GetActorEyesViewPoint(OutLocation, OutRotation);

	if (CameraComponent) {
		OutLocation = CameraComponent->GetComponentLocation();
	}
}

void ASCharacter::MulticastOnHealthChange_Implementation()
{
	
}

void ASCharacter::OnHealthChanged(USHealthComponent* OwnHealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	MulticastOnHealthChange();

	if (Health == 0.0f) {

		// Die
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMovementComponent()->StopMovementImmediately();
		DetachFromControllerPendingDestroy();
		SetLifeSpan(5.0);

		bDied = true;
	}
}

void ASCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASCharacter, Weapon);
	DOREPLIFETIME(ASCharacter, bDied);
}