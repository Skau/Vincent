// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger_SpawnActor.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"

#include "WorldActors/MovingPlatform.h"
#include "SpawnPoint.h"
#include "Player/PlayerCharacter.h"

// Sets default values
ATrigger_SpawnActor::ATrigger_SpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	RootComponent = TriggerVolume;

	bHasSpawned = false;
}

// Called when the game starts or when spawned
void ATrigger_SpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger_SpawnActor::OnBeginOverlap);
}

// Called every frame
void ATrigger_SpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrigger_SpawnActor::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		if (!bHasSpawned)
		{
			ActivateSpawnpoints();
			bHasSpawned = true;
		}
	}
}

void ATrigger_SpawnActor::ActivateSpawnpoints()
{
	if (Spawnpoints.Num() > 0)
	{
		for (ASpawnPoint* Spawnpoint : Spawnpoints)
		{
			Spawnpoint->Spawn();
		}
	}
}