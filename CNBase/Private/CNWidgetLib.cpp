// Fill out your copyright notice in the Description page of Project Settings.


#include "CNWidgetLib.h"
#include "CNGameLog.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Engine/Texture2D.h"

#pragma optimize( "", off )

bool UCNWidgetLib::IsParentContainDescendant(UUserWidget* Root, UUserWidget* Descendant)
{
	// UTexture2D a;

	//FStringobjectre

	//StaticLoadObject()

	return false;
}

int UCNWidgetLib::AddChildrenToGridPanel(UUniformGridPanel* Panel,
	int ColumnNum, TArray<UWidget*> Children)
{
	int Ret = 0;
	if (!Panel || !Children.Num()) {
		return Ret;
	}

	// Add children
	for (int i = 0; i < Children.Num(); ++i) {
		auto SlotWidget = Panel->AddChildToUniformGrid(Children[i]);

		if (SlotWidget) {
			SlotWidget->SetColumn(i % ColumnNum);
			SlotWidget->SetRow(i / ColumnNum);
			SlotWidget->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			SlotWidget->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			Ret++;
		}
	}

	return Ret;
}

#pragma optimize( "", on )