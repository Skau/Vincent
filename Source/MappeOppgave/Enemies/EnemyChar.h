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

	UFUNCTION(BlueprintCallable)
	void MoveEnemyToSpawnLocation() { SetActorLocation(SpawnLocation); }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Knockback(AActor* DamageCauser);

	class APlayerCharacter* Player = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float Health = 0;

private:
	FVector SpawnLocation = FVector(0);
};
