// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModel.generated.h"

class ASGameState;

/**
 * 
 */
UCLASS()
class COOPGAME_API ASGameModel : public AGameModeBase
{
	GENERATED_BODY()

private:

	ASGameModel();

	UPROPERTY(EditDefaultsOnly, Category = SpawnBots)
	int BotsNumberBegin;

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartPlay() override;

	/**
	 * Time delay of a wave
	 */
	UPROPERTY(EditDefaultsOnly)
	float SpawnBotsWaveDelay;

	FTimerHandle TimerSpawnBotsWave;

	UFUNCTION(BlueprintImplementableEvent)
	void BPSpawnBots(int BotNumber);

	void SpawnBots();

	void BeginWave();

	bool IsAllBotsDead();

	bool IsAllCharactersDead();

	/**
	* Change game state
	*/
	void GameOver(bool Success);

protected:

	int WaveNum;

	/**
	* The number of wave of enemy bots
	*/
	UPROPERTY(EditDefaultsOnly)
	int MaxWaveNum;
	
	ASGameState* GameState;
	
	bool bGameOver;
};
