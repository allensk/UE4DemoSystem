// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacterBase.h"

// Sets default values
APCharacterBase::APCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

