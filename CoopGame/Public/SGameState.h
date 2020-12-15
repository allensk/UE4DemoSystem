// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CNGameState.h"
#include "SGameState.generated.h"

UENUM()
enum ESGameState {
	WaitingStart,
	InProgress,
	GameOver,
	GameSuccess
};

/**
 * 
 */
UCLASS()
class COOPGAME_API ASGameState : public ACNGameState
{
	GENERATED_BODY()
public:
	ASGameState();
	~ASGameState() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(BlueprintImplementableEvent)
	void SetBPGameState(ESGameState InGameState);

	void SetGameState(ESGameState InGameState);

	UFUNCTION(BlueprintImplementableEvent)
	void SetBPWaveNum(int InWaveNum);

	void SetWaveNum(int InWaveNum);

	UFUNCTION()
	void OnRepWaveNum();

	UFUNCTION()
	void OnRepGameState();

protected:
	
	UPROPERTY(ReplicatedUsing = OnRepWaveNum)
	int WaveNum;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepGameState)
	TEnumAsByte<ESGameState> GameState;

private:

};
