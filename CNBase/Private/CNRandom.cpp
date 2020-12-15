// Fill out your copyright notice in the Description page of Project Settings.


#include "CNRandom.h"

CNRandom::~CNRandom()
{
}

float CNRandom::GetFactor(ECNObjectLevel Level, ECNAbilityType Type)
{
	return LevelFactors[static_cast<int>(Level)];
}