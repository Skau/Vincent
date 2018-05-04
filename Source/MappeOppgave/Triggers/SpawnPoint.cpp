// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Hammer.h"
#include "TimerManager.h"
#include "GameModes/MappeOppgaveGameModeBase.h"

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMappeOppgaveGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (bIsHammer && ActorToSpawn)
	{
		GetWorld()->SpawnActor<AHammer>(ActorToSpawn, GetActorLocation(), GetActorRotation());
	}
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpawnedActor || !bSpawnUntilFracturedWall) { return; }

	if(!bWallIsFractured)
	{
		if (SpawnedActor->IsActorBeingDestroyed())
		{
			if (!bIsTimerStarted)
			{
				UE_LOG(LogTemp, Warning, TEXT("Spawned Actor Being Destroyed"));

				GetWorld()->GetTimerManager().SetTimer(SpawnAgain, this, &ASpawnPoint::Spawn, 1.f);

				UE_LOG(LogTemp, Warning, TEXT("Started Timer"));
				bIsTimerStarted = true;
			}
		}
	}
}

void ASpawnPoint::Spawn()
{
	if (ActorToSpawn && !bWallIsFractured)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(), GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("Spawned Actor"));
		bIsTimerStarted = false;
	}
}

