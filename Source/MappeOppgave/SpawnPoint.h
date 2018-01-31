// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"

#include "SpawnPoint.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

	void Spawn();

	UPROPERTY(EditAnywhere)
	UClass* ActorToSpawn;
	
	UPROPERTY(EditAnywhere)
	bool bIsHammer;
	
};
