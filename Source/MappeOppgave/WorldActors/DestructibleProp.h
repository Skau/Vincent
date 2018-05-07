// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleActor.h"
#include "DestructibleProp.generated.h"

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API ADestructibleProp : public ADestructibleActor
{
	GENERATED_BODY()
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	
	
};
