// Fill out your copyright notice in the Description page of Project Settings.


#include "CNUsableActor.h"
#include "CNGameLog.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACNUsableActor::ACNUsableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCanEverAffectNavigation(false);
	RootComponent = StaticMesh;

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ACNUsableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACNUsableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACNUsableActor::IsUsable_Implementation()
{
	return Usable;
}

bool ACNUsableActor::Use_Implementation(APlayerController* PlayerController)
{
	return true;
}

bool ACNUsableActor::BeginOutlineFocus_Implementation()
{
	if (StaticMesh) {
		StaticMesh->SetRenderCustomDepth(true);
	}

	return true;
}

bool ACNUsableActor::EndOutlineFocus_Implementation()
{
	if (StaticMesh) {
		StaticMesh->SetRenderCustomDepth(false);
	}

	return true;
}
