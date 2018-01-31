// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Hammer.h"

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (bIsHammer && ActorToSpawn != nullptr)
	{
		auto Player = (APlayerCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		auto Hammer = GetWorld()->SpawnActor<AHammer>(ActorToSpawn, GetActorLocation(), GetActorRotation());

		Player->SetOldHammer(Hammer);
	}
}

void ASpawnPoint::Spawn()
{
	if (ActorToSpawn != nullptr)
	{
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(), GetActorRotation());
	}
}

