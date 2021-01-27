// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CNGameState.h"
#include "PGameState.generated.h"

UENUM(BlueprintType)
enum class E_PGameStage : uint8 {
	WaitingStart,
	FirstStage,
	SecondStage,
	GameOver,
	GameSuccess
};

ENUM_CLASS_FLAGS(E_PGameStage)

/**
 * 
 */
UCLASS()
class COOPGAME_API APGameState : public ACNGameState
{
	GENERATED_BODY()
public:
	APGameState();
	virtual ~APGameState() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	E_PGameStage GetFirstStage() { return TestGameFirstStage; }

	//////////////////////////////////////////////////////////

	UFUNCTION(Client, Reliable)
	void ClientSetGameStage(E_PGameStage Stage);

	E_PGameStage GetGameStage() { return GameStage; }
	void SetGameStage(E_PGameStage Stage);

	void SetWaveNum(int InWaveNum);

	UFUNCTION(BlueprintImplementableEvent)
	void BPSetWaveNum(int InWaveNum);

	UFUNCTION()
	void OnRepWaveNum();

	UFUNCTION(BlueprintImplementableEvent)
	void BPSetGameState(E_PGameStage Stage);

	UFUNCTION()
	void OnRepGameState();

protected:
	
	// Monster Wave
	UPROPERTY(ReplicatedUsing = OnRepWaveNum)
	int WaveNum;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepGameState)
	E_PGameStage GameStage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	E_PGameStage TestGameFirstStage;
};
