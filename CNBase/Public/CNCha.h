// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CNAttriBase.h"
#include "CNCha.generated.h"

class FCNChaStore;

/**
 * In case of cheating, I decide not to storage temporary value.
 */
UCLASS()
class CNBASE_API UCNCha : public UObject
{
	GENERATED_BODY()

public:
	UCNCha() = default;
	
	/** Get basic ability*/
	UFUNCTION(BlueprintCallable)
	FCNChaBase& GetBaseAb() { return Cur; }

protected:
	void UpdateAb();

	TSharedPtr<FCNChaBase> Base{ nullptr };
	FCNChaBase  Cur;
	ECNObjectLevel Level{ ECNObjectLevel::FIRST };
};
