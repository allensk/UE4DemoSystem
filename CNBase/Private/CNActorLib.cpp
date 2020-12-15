// Fill out your copyright notice in the Description page of Project Settings.

#include "CNActorLib.h"

#include "GameFramework/Actor.h"

AActor* UCNActorLib::GetNearestActor(AActor* Origin, TArray<AActor*> Actors, FName Tag)
{
	AActor* RetActor = nullptr;

	if (!Origin || !Actors.Num())
		return RetActor;

	// Filter by tag
	TArray<AActor*> FilteredActors;
	if (Tag.IsValid()) {
		for (auto x : Actors) {
			if (x->ActorHasTag(Tag))
			FilteredActors.Push(x);
		}
	}
	else {
		FilteredActors = Actors;
	}
	
	// Compare with max float
	float MaxDistance = MAX_FLT;
	for (auto x : FilteredActors) {
		float TmpDistance = (x->GetActorLocation() - Origin->GetActorLocation()).Size();
		if (TmpDistance <= MaxDistance) {
			MaxDistance = TmpDistance;
			RetActor = x;
		}
	}

	return RetActor;
}