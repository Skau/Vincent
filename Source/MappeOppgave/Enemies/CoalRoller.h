// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyChar.h"
#include "CoalRoller.generated.h"

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API ACoalRoller : public AEnemyChar
{
	GENERATED_BODY()

public:
	ACoalRoller();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	
};
