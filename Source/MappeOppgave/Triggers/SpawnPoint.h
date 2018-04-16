// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"

#include "SpawnPoint.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Spawn();


	UPROPERTY(EditAnywhere)
	UClass* ActorToSpawn;

private:
	UPROPERTY(EditAnywhere)
	AActor* SpawnUntillDestroyed = nullptr;

	UPROPERTY(EditAnywhere)
	bool bIsHammer;

	bool bIsTimerStarted;
	
	FTimerHandle SpawnAgain;

	AActor* SpawnedActor = nullptr;
};
