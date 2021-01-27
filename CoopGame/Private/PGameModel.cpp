// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameModel.h"
#include "PGameState.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Public/TimerManager.h"
#include "EngineGlobals.h"

#include "GameFramework/Character.h"
#include "EnvironmentQuery/EnvQueryManager.h"

#include "CoopGame.h"
#include "STrackBot.h"

namespace {

E_PGameStage GetGameStage(APGameModel* Model) {

	if (Model) {
		if (auto State = Model->GetGameState<APGameState>()) {
			return State->GetGameStage();
		}
	}

	return E_PGameStage::GameOver;
}

};

APGameModel::APGameModel()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;

	WaveNum = 0;
	SpawnBotsWaveDelay = 5.0f;
	BotsNumberBegin = 2;
	MaxWaveNum = 3;
}

void APGameModel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bGameOver) {
		return;
	}

	if (GetGameStage(this) == E_PGameStage::FirstStage) {
		
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
}

bool APGameModel::IsAllBotsDead()
{
	TArray<AActor*> Actors;
	TSubclassOf<ASTrackBot> TrackBotClass(ASTrackBot::StaticClass());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TrackBotClass, Actors);
	
	if (Actors.Num()) {
		return false;
	}
	
	return true;
}

bool APGameModel::IsAllCharactersDead()
{
	TArray<AActor*> Actors;
	TSubclassOf<ACharacter> ChaClass(ACharacter::StaticClass());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ChaClass, Actors);
	if (Actors.Num()) {
		return false;
	}
	return true;
}

void APGameModel::BeginFirstStage()
{
	if (auto State = GetGameState<APGameState>()) {
		State->SetGameStage(State->GetFirstStage());
	}

	// BeginWave();
}

void APGameModel::StartPlay()
{
	Super::StartPlay();
	ensure(GetGameState<APGameState>());

	BeginFirstStage();
}

void APGameModel::BeginWave()
{
	WaveNum++;

	if (auto State = GetGameState<APGameState>()) {
		State->SetWaveNum(WaveNum);
	}

	GetWorldTimerManager().SetTimer(TimerSpawnBotsWave, this, &APGameModel::SpawnBots, SpawnBotsWaveDelay, false);
	UE_LOG(GameLog, Display, TEXT("%d wave enemy after %fs"), WaveNum, SpawnBotsWaveDelay);
}

void APGameModel::SpawnBots()
{
	if (WaveNum <= MaxWaveNum) {

		UE_LOG(GameLog, Log, TEXT("Spawn bots %d"), BotsNumberBegin);

		BPSpawnBots(BotsNumberBegin);
	}

	BotsNumberBegin *= 2;
}

void APGameModel::GameOver(bool Success)
{
	UE_LOG(GameLog, Log, TEXT("Game Over!"));

	bGameOver = true;

	if (auto State = GetGameState<APGameState>()) {
		State->SetGameStage(E_PGameStage::GameOver);
	}
}