// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp_Heart.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

// Sets default values
APickUp_Heart::APickUp_Heart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	RootComponent = TriggerVolume;

	TriggerVolume->SetGenerateOverlapEvents(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APickUp_Heart::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APickUp_Heart::OnBeginOverlap);
}

// Called every frame
void APickUp_Heart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, 1, 0));
}

void APickUp_Heart::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		auto Player = Cast<APlayerCharacter>(OtherActor);
	
		if (Player->GetHealth() < 3)
		{
			Player->IncrementHealth();
			if (PickupSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
			}

			Destroy();
		}
	}
}

