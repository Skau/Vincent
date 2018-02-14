// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyChar.h"
#include "BombRoller.generated.h"

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API ABombRoller : public AEnemyChar
{
	GENERATED_BODY()
	
public:
	ABombRoller();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Explode();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class URadialForceComponent* ExplosionForce = nullptr;
	
};
