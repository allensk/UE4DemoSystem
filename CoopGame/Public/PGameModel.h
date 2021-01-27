// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PGameModel.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API APGameModel : public AGameMode
{
	GENERATED_BODY()

private:

	APGameModel();

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartPlay() override;

	/**
	 * Time delay of a wave
	 */
	UPROPERTY(EditDefaultsOnly)
	float SpawnBotsWaveDelay;

	UFUNCTION(BlueprintImplementableEvent)
	void BPSpawnBots(int BotNumber);

	void SpawnBots();

	void BeginWave();

	bool IsAllBotsDead();

	bool IsAllCharactersDead();

	void BeginFirstStage();

	/**
	* Change game state
	*/
	void GameOver(bool Success);

private:

	int WaveNum;
	bool bGameOver;

	/**
	* The number of wave of enemy bots
	*/
	UPROPERTY(EditDefaultsOnly)
	int MaxWaveNum;

	UPROPERTY(EditDefaultsOnly, Category = SpawnBots)
	int BotsNumberBegin;

	FTimerHandle TimerSpawnBotsWave;
};
