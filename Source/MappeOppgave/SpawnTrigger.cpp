// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnTrigger.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"

#include "SpawnPoint.h"
#include "PlayerCharacter.h"

// Sets default values
ASpawnTrigger::ASpawnTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (TriggerVolume == nullptr) { return; }

	RootComponent = TriggerVolume;

	bHasSpawned = false;
}

// Called when the game starts or when spawned
void ASpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ASpawnTrigger::OnBeginOverlap);
}

// Called every frame
void ASpawnTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnTrigger::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

void ASpawnTrigger::ActivateSpawnpoints()
{
	if (Spawnpoints.Num() > 0)
	{
		for (ASpawnPoint* Spawnpoint : Spawnpoints)
		{
			Spawnpoint->Spawn();
		}
	}
}
