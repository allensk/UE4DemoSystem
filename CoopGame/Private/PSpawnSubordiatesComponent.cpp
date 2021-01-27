// Fill out your copyright notice in the Description page of Project Settings.

#include "PSpawnSubordiatesComponent.h"

#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/KismetArrayLibrary.h"


#include "CNGameLog.h"

// Sets default values for this component's properties
UPSpawnSubordiatesComponent::UPSpawnSubordiatesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	DesiredSpawnNum = 0;

	// ...
}

// Called when the game starts
void UPSpawnSubordiatesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPSpawnSubordiatesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPSpawnSubordiatesComponent::SpawnSubordinates()
{
	if (!DesiredSpawnNum) {
		return;
	}

	if (GetOwnerRole() == ROLE_Authority) {

		ensure(GetOwner());
		FEnvQueryRequest Request(SpawnEQS, GetOwner());

		Request.Execute(EEnvQueryRunMode::AllMatching,
			this,
			&UPSpawnSubordiatesComponent::EQSQueryFinished);
	}

}

void UPSpawnSubordiatesComponent::EQSQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	auto p = Result.Get();
	if (p && p->IsSuccsessful()) {
		TArray<FVector> Vectors;
		p->GetAllAsLocations(Vectors);

		// Random array
		int32 LastIndex = Vectors.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i) {
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index) {
				Vectors.SwapMemory(i, Index);
			}
		}

		// 
		int SpawnNum = FMath::Min((int32)DesiredSpawnNum, Vectors.Num());

		FTransform TransForm{};
		FActorSpawnParameters Params{};
		Params.Owner = GetOwner();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Spawn loop
		for (int i = 0; i < SpawnNum; ++i) {

			// Get a random location in existing location points.
			int Index = FMath::RandRange(0, Vectors.Num() - 1);
			TransForm.SetLocation(Vectors[Index]);
			AActor* Actor = GetWorld()->SpawnActor<AActor>(SubordinateClass, TransForm, Params);
			
			// Add tags
			Actor->Tags = GetOwner()->Tags;
			Actor->Tags.Add(TEXT("Subordinate"));
			
			// Remove used location
			Vectors.RemoveAt(Index, 1, true);
		}
	}
}

