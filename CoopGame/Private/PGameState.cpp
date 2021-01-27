// Fill out your copyright notice in the Description page of Project Settings.


#include "PGameState.h"
#include "Net/UnrealNetwork.h"
#include "CNGameLog.h"

APGameState::APGameState()
{
	UE_LOG(CNLog, Log, TEXT("Construct APGameState"));
	GameStage = E_PGameStage::WaitingStart;
	TestGameFirstStage = E_PGameStage::FirstStage;
}

APGameState::~APGameState()
{
	UE_LOG(CNLog, Log, TEXT("Destruct APGameState"));
}

void APGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APGameState, WaveNum);
	DOREPLIFETIME(APGameState, GameStage);
}

void APGameState::ClientSetGameStage_Implementation(E_PGameStage InGameState)
{
	BPSetGameState(GameStage);
}

void APGameState::SetGameStage(E_PGameStage InGameState)
{
	if (Role == ROLE_Authority) {
		ClientSetGameStage(InGameState);
		GameStage = InGameState;
		// OnRepGameState();
	}
}

void APGameState::SetWaveNum(int InWaveNum)
{
	if (Role == ROLE_Authority) {
		WaveNum = InWaveNum;
		OnRepWaveNum();
	}
}

void APGameState::OnRepWaveNum()
{
	BPSetWaveNum(WaveNum);
}

void APGameState::OnRepGameState()
{
	BPSetGameState(GameStage);
}