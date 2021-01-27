// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CNUsableActorInterface.h"

#include "CNUsableActor.generated.h"

UCLASS()
class CNBASE_API ACNUsableActor : public AActor, public ICNUsableActorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACNUsableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsUsable_Implementation() override;

	virtual bool Use_Implementation(APlayerController* PlayerController) override;

	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Usable)
	FText GetUseActionText();*/

	virtual bool BeginOutlineFocus_Implementation() override;

	virtual bool EndOutlineFocus_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Usable")
	bool Usable{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Usable")
	bool Used{ false };

	UPROPERTY(EditDefaultsOnly, Category = Explosive)
	USoundBase* UsedSound;
};
