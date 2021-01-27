// Fill out your copyright notice in the Description page of Project Settings.


#include "PArcherCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Net/UnrealNetwork.h"

#include "CNGameLog.h"

// Sets default values
APArcherCharacter::APArcherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArm);

	// GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON_COLLISION, ECR_Block);
	
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void APArcherCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APArcherCharacter::BeginCrouch()
{
	Crouch();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Crouch"));
}

void APArcherCharacter::EndCrouch()
{
	UnCrouch();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Crouch"));
}

void APArcherCharacter::BeginZoom()
{
	// WantZoom = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Zoom"));
}

void APArcherCharacter::EndZoom()
{
	// WantZoom = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Zoom"));
}

void APArcherCharacter::Jump()
{
	Super::Jump();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Jump"));
}