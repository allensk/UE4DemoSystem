// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModel.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Public/TimerManager.h"
#include "EngineGlobals.h"

#include "GameFramework/Character.h"
#include "EnvironmentQuery/EnvQueryManager.h"

#include "CoopGame.h"
#include "STrackBot.h"
#include "SGameState.h"


ASGameModel::ASGameModel()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;

	WaveNum = 0;
	SpawnBotsWaveDelay = 5.0f;
	BotsNumberBegin = 2;
	MaxWaveNum = 3;
}

void ASGameModel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bGameOver) {
		return;
	}
		
	// Check if all bots are dead
	if (IsAllBotsDead()) {

		// Check if spawning bots event is going on
		if (!GetWorldTimerManager().IsTimerActive(TimerSpawnBotsWave)) {

			// All bots are spawned and dead
			if (WaveNum == MaxWaveNum) {
				// Check if any player is alive
				if (!IsAllCharactersDead()) {
					GameOver(true);
				}
			}
			else {
				BeginWave();
			}
		}
	}

	// If all players are dead, end game
	if (IsAllCharactersDead()) {
		GameOver(false);
	}
}

bool ASGameModel::IsAllBotsDead()
{
	TArray<AActor*> Actors;
	TSubclassOf<ASTrackBot> TrackBotClass(ASTrackBot::StaticClass());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TrackBotClass, Actors);
	
	if (Actors.Num()) {
		return false;
	}
	
	return true;
}

bool ASGameModel::IsAllCharactersDead()
{
	TArray<AActor*> Actors;
	TSubclassOf<ACharacter> ChaClass(ACharacter::StaticClass());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ChaClass, Actors);
	if (Actors.Num()) {
		return false;
	}
	return true;
}

void ASGameModel::StartPlay()
{
	Super::StartPlay();

	GameState = GetGameState<ASGameState>();
	ensure(GameState);
	
	bGameOver = true;

	// APlayerController
	
	// BeginWave();
}

void ASGameModel::BeginWave()
{
	WaveNum++;
	GetWorldTimerManager().SetTimer(TimerSpawnBotsWave, this, &ASGameModel::SpawnBots, SpawnBotsWaveDelay, false);
	GameState->SetWaveNum(WaveNum);

	UE_LOG(GameLog, Display, TEXT("%d wave enemy after %fs"), WaveNum, SpawnBotsWaveDelay);
}

void ASGameModel::SpawnBots()
{
	if (WaveNum <= MaxWaveNum) {

		UE_LOG(GameLog, Log, TEXT("Spawn bots %d"), BotsNumberBegin);

		BPSpawnBots(BotsNumberBegin);
	}

	BotsNumberBegin *= 2;
}

void ASGameModel::GameOver(bool Success)
{
	UE_LOG(GameLog, Log, TEXT("Game Over!"));

	ASGameState* State = GetGameState<ASGameState>();
	GameState->SetGameState(ESGameState::GameOver);

	bGameOver = true;
}