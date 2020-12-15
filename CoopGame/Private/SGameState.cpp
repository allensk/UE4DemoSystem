// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameState.h"
#include "Net/UnrealNetwork.h"
#include "GameLog.h"

ASGameState::ASGameState()
{
	UE_LOG(GameLog, Log, TEXT("Construct ASGameState"));
	GameState = ESGameState::WaitingStart;
}

ASGameState::~ASGameState()
{
	UE_LOG(GameLog, Log, TEXT("Destruct ASGameState"));
}

void ASGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGameState, WaveNum);
	DOREPLIFETIME(ASGameState, GameState);
}

void ASGameState::SetGameState(ESGameState InGameState)
{
	if (Role == ROLE_Authority) {
		GameState = InGameState;
		OnRepGameState();
	}
}

void ASGameState::SetWaveNum(int InWaveNum)
{
	if (Role == ROLE_Authority) {
		WaveNum = InWaveNum;
		OnRepWaveNum();
	}
}

void ASGameState::OnRepWaveNum()
{
	SetBPWaveNum(WaveNum);
}

void ASGameState::OnRepGameState()
{
	SetBPGameState(GameState);
}