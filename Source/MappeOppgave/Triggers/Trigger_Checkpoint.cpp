// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger_Checkpoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"

// Sets default values
ATrigger_Checkpoint::ATrigger_Checkpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerVolume");
	RootComponent = TriggerVolume;

	CheckpointStand = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointStand");
	CheckpointStand->SetupAttachment(RootComponent);

	CheckpointHandle = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointHandle");
	CheckpointHandle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrigger_Checkpoint::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger_Checkpoint::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATrigger_Checkpoint::OnEndOverlap);

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ATrigger_Checkpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Updates mesh depending on if the player is holding the hammer or not
	if (Player->getIsHoldingHammer())
	{
		if (CheckpointHandle->IsActive())
		{
			DeactivateMesh(CheckpointHandle);
		}
	}
	else
	{
		if (!CheckpointHandle->IsActive())
		{
			ActivateMesh(CheckpointHandle);
		}
	}
}

void ATrigger_Checkpoint::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Updates spawnlocation and displays appropriate checkpoint widget
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Player->SetBIsCloseEnough(true);
		if (!bIsWidgetPlaying)
		{
			bIsWidgetPlaying = true;

			if (IsCurrentSpawn)
			{
				CreateCheckpointTakenWidget();
			}
			else
			{
				Player->SetNewSpawnPoint(GetActorLocation() + FVector(-100, 0, 0));
				IsCurrentSpawn = true;
				CreateCheckpointPromptWidget();
			}
		}
	}
}

void ATrigger_Checkpoint::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Player->SetBIsCloseEnough(false);
	}
}

void ATrigger_Checkpoint::ActivateMesh(UStaticMeshComponent * Mesh)
{
	Mesh->SetActive(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetVisibility(true);
}

void ATrigger_Checkpoint::DeactivateMesh(UStaticMeshComponent* Mesh)
{
	Mesh->SetActive(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetVisibility(false);
}


