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

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Knockback(AActor* DamageCauser);

	class APlayerCharacter* Player;

	UPROPERTY(EditDefaultsOnly)
	float Health;

	bool bHasBeenKnockedbackRecently = false;
};
