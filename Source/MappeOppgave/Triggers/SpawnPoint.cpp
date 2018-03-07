// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Hammer.h"

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (bIsHammer && ActorToSpawn)
	{
		auto Hammer = GetWorld()->SpawnActor<AHammer>(ActorToSpawn, GetActorLocation(), GetActorRotation());
	}
}

void ASpawnPoint::Spawn()
{
	if (ActorToSpawn)
	{
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(), GetActorRotation());
	}
}

