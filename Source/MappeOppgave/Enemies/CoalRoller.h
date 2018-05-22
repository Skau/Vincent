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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem * DeathParticle = nullptr;

	UPROPERTY(EditDefaultsOnly)
	int Damage = 1;

	bool bHasBeenKnockedbackRecently = false;

	UFUNCTION(BlueprintCallable)
	void ResetHasBeenKnockedBack() { bHasBeenKnockedbackRecently = false; }

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ExplosionSound = nullptr;
};
