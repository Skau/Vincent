// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger_Teleporter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "PlayerCharacter.h"

// Sets default values
ATrigger_Teleporter::ATrigger_Teleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = TriggerVolume;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrigger_Teleporter::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger_Teleporter::OnBeginOverlap);
}

// Called every frame
void ATrigger_Teleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrigger_Teleporter::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ConnectedTeleporter)
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			OtherActor->TeleportTo(ConnectedTeleporter->GetActorLocation(), GetActorRotation());
		}
	}
}
