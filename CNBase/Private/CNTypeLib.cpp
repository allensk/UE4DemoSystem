// Fill out your copyright notice in the Description page of Project Settings.


#include "CNTypeLib.h"

FName UCNTypeLib::GetLevelSTKey(ECNObjectLevel Level)
{
	FName Ret;
	switch (Level) {
	case ECNObjectLevel::FIRST:
		Ret = FName(TEXT("LevelFirst"));
		break;
	case ECNObjectLevel::SECOND:
		Ret = FName(TEXT("LevelSecond"));
		break;
	case ECNObjectLevel::THIRD:
		Ret = FName(TEXT("LevelThird"));
		break;
	case ECNObjectLevel::FORTH:
		Ret = FName(TEXT("LevelForth"));
		break;
	case ECNObjectLevel::FIFTH:
		Ret = FName(TEXT("LevelFifth"));
		break;
	default:
		Ret = FName(TEXT("Unfound"));
		break;
	}

	return Ret;
}