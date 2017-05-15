// Copyright 2017 Krivosheya Mikhail. All Rights Reserved.
#include "DialogSystemRuntime.h"
#include "EdGraph/EdGraphPin.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "StoryInformationManager.h"
#include "DialogImplementer.h"
#include "DialogPhrase.h"

void UDialogNode::Invoke(class UDialogImplementer* Implementer)
{
}

bool UDialogNode::Check(UDialogImplementer* Implementer)
{
	return false;
}

TArray<UDialogNode*> UDialogNode::GetChilds()
{
	return Childs;
}

void UDialogPhrase::Invoke(UDialogImplementer* Implementer)
{
	for (auto key : Data.GiveKeys)
		UStoryKeyManager::AddKey(key);

	for (auto key : Data.RemoveKeys)
		UStoryKeyManager::RemoveKey(key);
	
	if (UID.IsValid())
		UStoryKeyManager::AddKey(*(Implementer->Asset->Name.ToString() + UID.ToString()), EStoryKeyTypes::DialogPhrases);

	for (auto& Event : Data.CustomEvents)
		Event.Invoke(Implementer);
}

bool UDialogPhrase::Check(UDialogImplementer* Implementer)
{
	for (auto key : Data.CheckHasKeys)
	{
		if (UStoryKeyManager::DontHasKey(key))
			return false;
	}

	for (auto key : Data.CheckDontHasKeys)
	{
		if (UStoryKeyManager::HasKey(key))
			return false;
	}

	for (auto& Conditions : Data.CustomConditions)
	{
		if (!Conditions.InvokeCheck(Implementer))
			return false;
	}

	return true;
}