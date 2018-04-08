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

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Knockback(AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void ResetHasBeenKnockedBack() { bHasBeenKnockedbackRecently = false; }

private:
	UPROPERTY(EditDefaultsOnly)
	float Health;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathParticle = nullptr;

	class APlayerCharacter* Player;

	FTimerHandle TH_HasTakenDamageTimer;

	bool bHasTakenDamageRecently = false;
	bool bHasBeenKnockedbackRecently = false;

	void ResetHasTakenDamageTimer() { bHasTakenDamageRecently = false; }
};
