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
	ASpawnPoint();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Spawn();

	UFUNCTION(BlueprintCallable)
	void SetWallIsFractured() { bWallIsFractured = true; }

private:
	bool bWallIsFractured = false;
	
	UPROPERTY(EditAnywhere)
	UClass* ActorToSpawn;

	UPROPERTY(EditAnywhere)
	bool bIsHammer;

	UPROPERTY(EditAnywhere)
	bool bSpawnUntilFracturedWall;

	bool bIsTimerStarted;
	
	FTimerHandle SpawnAgain;

	AActor* SpawnedActor = nullptr;
};
