// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyChar.generated.h"

UCLASS()
class MAPPEOPPGAVE_API AEnemyChar : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyChar();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathParticle = nullptr;

private:
	void ResetAttackTimer() { bHasAttackedRecently = false; }

	UPROPERTY(EditAnywhere)
	float Health;
	
	bool bHasAttackedRecently;

	FTimerHandle TH_Attack;
	FTimerHandle TH_ResetKnockback;

	FVector Direction;

	class APlayerCharacter* Player;

	bool bWasHit = false;

	void SetHit() { bWasHit = false; }
};
