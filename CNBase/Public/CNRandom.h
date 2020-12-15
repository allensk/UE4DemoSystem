// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CNAttriBase.h"

const float MilitaryLevelFactor[] = {
	1.0f,
	1.2f,
	1.4f,
	1.6f,
	1.8f,
	2.0f
};

const float LevelFactors[] = {
	1.0f,
	1.2f,
	1.4f,
	1.6f,
	1.8f,
	2.0f
};

/**
 * 
 */
class CNBASE_API CNRandom
{
public:
	CNRandom(ECNObjectLevel Level = ECNObjectLevel::SECOND,
		ECNAbilityType Type = ECNAbilityType::NONE) {
		this->Level = Level;
		this->Type = Type;
	}
	
	~CNRandom();

	float GetFactor() {
		return LevelFactors[static_cast<int>(Level)];
	}

	static float GetFactor(ECNObjectLevel Level, ECNAbilityType Type);

private:
	ECNAbilityType Type;
	ECNObjectLevel Level;
};
