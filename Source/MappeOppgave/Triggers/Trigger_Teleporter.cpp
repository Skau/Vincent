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

	SetDoorOpen();
}

void ATrigger_Teleporter::SetDoorOpen()
{
	if (!bIsDoorOpen)
	{
		if (DoorMesh->RelativeRotation.Yaw > 0)
		{
			CloseDoor();
		}
	}
	else
	{
		if (DoorMesh->RelativeRotation.Yaw < 170.f)
		{
			OpenDoor();
		}
	}
}

void ATrigger_Teleporter::CloseDoor()
{
	DoorMesh->AddRelativeRotation(FRotator(0, -3.5f, 0));
}

void ATrigger_Teleporter::OpenDoor()
{
	DoorMesh->AddRelativeRotation(FRotator(0, 3.5f, 0));
}

void ATrigger_Teleporter::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin!"));
	if (ConnectedTeleporter)
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			if (!Player->GetIsBeingTeleported())
			{
				bIsDoorOpen = true;
				Player->SetIsBeingTeleported(true);
				ConnectedTeleporter->SetIsDoorOpen(false);
				UE_LOG(LogTemp, Warning, TEXT("Starting Timer!"));
				GetWorld()->GetTimerManager().SetTimer(TH_TeleportTimer, this, &ATrigger_Teleporter::TeleportPlayer, 1.5f);
			}
			else
			{
				bIsDoorOpen = false;
			}
		}
	}
}

void ATrigger_Teleporter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End!"));
	Player->SetIsBeingTeleported(false);

}

void ATrigger_Teleporter::TeleportPlayer()
{
	if (Player->GetIsBeingTeleported())
	{
		UE_LOG(LogTemp, Warning, TEXT("Doing Teleport!"));
		Player->TeleportTo(ConnectedTeleporter->GetActorLocation() + FVector(0,0,30), GetActorRotation(), false, true);
		Player->SetIsBeingTeleported(false);
	}
}