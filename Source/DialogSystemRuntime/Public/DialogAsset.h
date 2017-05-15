// Copyright 2017 Krivosheya Mikhail. All Rights Reserved.
#pragma once

#include "Engine/DataAsset.h"
#include "DialogPhrase.h"
#include "DialogAsset.generated.h"

UCLASS(Blueprintable)
class DIALOGSYSTEMRUNTIME_API UDialogAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY()
	UDialogPhrase* RootNode;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "DialogScript"))
	TSubclassOf<class ADialogScript> DialogScriptClass;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* UpdateGraph;
#endif	// WITH_EDITORONLY_DATA

	UDialogAsset();
};