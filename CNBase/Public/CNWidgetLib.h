// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNWidgetLib.generated.h"

class UUserWidget;
class UUniformGridPanel;

/**
 * 
 */
UCLASS(meta = (ScriptName = "GenericWidgetLibrary"))
class CNBASE_API UCNWidgetLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Wrapper on UWidget::FindChildContainingDescendant
	 */
	UFUNCTION(BlueprintCallable, Category = Widget)
	static bool IsParentContainDescendant(UUserWidget* Root, UUserWidget* Descendant);

	UFUNCTION(BlueprintCallable, Category = Widget)
	static int AddChildrenToGridPanel(UUniformGridPanel* Panel, int ColumnNum, TArray<UWidget*> Children);
};
