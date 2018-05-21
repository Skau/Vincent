// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetLastMap(const FName& MapName) { LastMap = MapName; }

	UFUNCTION(BlueprintPure)
	FName GetLastMap() { return LastMap; }
	
private:

	FName LastMap = "";
};
