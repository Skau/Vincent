// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MappeOppgaveGameModeBase.generated.h"

// Forward declarations
class AEnemyChar;

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API AMappeOppgaveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	int GetCrystalsDestroyed() { return CrystalsDestroyed; }

	void IncreaseCrystalsDestroyed() { CrystalsDestroyed++; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<AEnemyChar*>& GetAllEnemies() { return AllEnemies; }

	void AddEnemyToAllEnemies(AEnemyChar* Enemy) { if (Enemy) { AllEnemies.Add(Enemy); } }

	void RemoveEnemyFromAllEnemies(AEnemyChar* Enemy) { if (Enemy) { AllEnemies.Remove(Enemy); } }

protected:
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* MusicSound;

private:
	int CrystalsDestroyed = 0;

	TArray<AEnemyChar*> AllEnemies;
	
	
};
