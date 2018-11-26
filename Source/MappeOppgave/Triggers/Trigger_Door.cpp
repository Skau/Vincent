// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger_Door.h"

#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "WorldActors/Door.h"
#include "WorldActors/Cube.h"
#include "Player/PlayerCharacter.h"
#include "Player/Hammer.h"


// Sets default values
ATrigger_Door::ATrigger_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	TriggerVolume->SetGenerateOverlapEvents(true);
	RootComponent = TriggerVolume;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrigger_Door::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger_Door::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATrigger_Door::OnEndOverlap);
}

// Called every frame
void ATrigger_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrigger_Door::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) || OtherActor->IsA(AHammer::StaticClass()) || OtherActor->IsA(ACube::StaticClass()))
	{
		NumberOfOverlappingActors++;
		if (Door && NumberOfOverlappingActors > 0)
		{
			Door->SetActorHiddenInGame(true);
			Door->SetActorEnableCollision(false);
		}
	}
}

void ATrigger_Door::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) || OtherActor->IsA(AHammer::StaticClass()) || OtherActor->IsA(ACube::StaticClass()))
	{
		NumberOfOverlappingActors--;
		if (Door && NumberOfOverlappingActors <= 0)
		{
			Door->SetActorHiddenInGame(false);
			Door->SetActorEnableCollision(true);
		}
	}
}

