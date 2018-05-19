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

	if (bPlayerStartsInside)
	{
		OpenDoorFirstTime();
	}
	else
	{
		if (DoorMesh)
			DoorMesh->SetRelativeRotation(FRotator(0, 180, 0));
	}
}

// Called every frame
void ATrigger_Teleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrigger_Teleporter::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap"))

		bPlayerIsInside = true;

		CloseDoor();
		
	}
	
}

void ATrigger_Teleporter::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnEndOverlap"))

		bPlayerIsInside = false;

		OpenDoor();
	}
}

void ATrigger_Teleporter::TeleportPlayer()
{
	if (Player->GetIsBeingTeleported() && bPlayerIsInside)
	{
		UE_LOG(LogTemp, Warning, TEXT("TeleportPlayer"))

		switch (TeleportToMap)	
		{
		case ETeleportToMap::Hub:
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("Hub"));
			break;
		case ETeleportToMap::Port:
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("Port"));
			break;
		case ETeleportToMap::Mines:
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("Mines3"));
			break;
		default:
			break;
		}
	}
}