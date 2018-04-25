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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

private:
	UFUNCTION(BlueprintCallable)
	void Explode();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem * ExplosionParticle;

	FTimerHandle TH_HasTakenDamageTimer;

	bool bHasBeenKnockedbackRecently = false;

	UFUNCTION(BlueprintCallable)
	void ResetHasBeenKnockedBack() { bHasBeenKnockedbackRecently = false; }

	UPROPERTY(EditDefaultsOnly)
	int Damage = 2;

	bool bHasTakenDamageRecently = false;

	void ResetHasTakenDamageTimer() { bHasTakenDamageRecently = false; }

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ExplosionSound = nullptr;
};
