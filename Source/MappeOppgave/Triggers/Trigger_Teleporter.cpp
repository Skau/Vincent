// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger_Teleporter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

#include "Player/PlayerCharacter.h"

// Sets default values
ATrigger_Teleporter::ATrigger_Teleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	TriggerVolume->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrigger_Teleporter::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger_Teleporter::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATrigger_Teleporter::OnEndOverlap);
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
			bPlayerIsInside = true;

			if (Player->GetIsBeingTeleported())
			{
				bIsTeleporter = true;
			}
			else if (!Player->GetIsBeingTeleported())
			{
				OpenDoor();
				bIsTeleporter = false;
			}

			if (bIsTeleporter)
			{
				CloseDoor();

				ConnectedTeleporter->CloseDoor();
			}
		}
	}
}

void ATrigger_Teleporter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ConnectedTeleporter)
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			bPlayerIsInside = false;

			if (Player->GetIsBeingTeleported())
			{
				bIsTeleporter = false;

				Player->SetIsBeingTeleported(false);
			}
			else if (!Player->GetIsBeingTeleported())
			{
				bIsTeleporter = false;

				Player->SetIsBeingTeleported(true);

				ConnectedTeleporter->OpenDoor();
			}
		}
	}
}

void ATrigger_Teleporter::TeleportPlayer()
{
	if (Player->GetIsBeingTeleported() && bIsTeleporter)
	{
		Player->TeleportTo(ConnectedTeleporter->GetActorLocation() + FVector(0, 0, 30), GetActorRotation(), false, true);
	}
}