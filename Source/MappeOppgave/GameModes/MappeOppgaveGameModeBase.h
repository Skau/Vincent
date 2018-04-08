// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MappeOppgaveGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API AMappeOppgaveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	int GetCrystalsDestroyed() { return CrystalsDestroyed; }
	void IncreaseCrystalsDestroyed() { CrystalsDestroyed++; }

private:
	int CrystalsDestroyed = 0;

};
