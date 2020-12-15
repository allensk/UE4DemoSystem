// Fill out your copyright notice in the Description page of Project Settings.


#include "CNGameGlobals.h"

#include "Paths.h"

FName GCodeSTable{ TEXT("/Game/Data/TranslationSource/ST_Code") };
FName GUISTable{ TEXT("/Game/Data/TranslationSource/ST_UI") };
FName GConverSTable{ TEXT("/Game/Data/TranslationSource/ST_Conversation") };
FName GItemSTable{ TEXT("/Game/Data/TranslationSource/ST_Item.ST_Item") };
//FName GItemSTable{ *(FPaths::ProjectContentDir().Append(TEXT("/Data/TranslationSource/ST_Item.ST_Item"))) };

// FName GCodeSTable{ *(FPaths::ProjectContentDir().Append(TEXT("/Data/TranslationSource/ST_Code"))) };
// FName GUISTable{ *(FPaths::ProjectContentDir().Append(TEXT("/Data/TranslationSource/ST_UI"))) };
// FName GConverSTable{ *(FPaths::ProjectContentDir().Append(TEXT("/Data/TranslationSource/ST_Conversation"))) };