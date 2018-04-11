// Fill out your copyright notice in the Description page of Project Settings.

#include "Crystal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Player/Hammer.h"
#include "Player/PlayerCharacter.h"
#include "GameModes/MappeOppgaveGameModeBase.h"
#include "CrystalIndicator.h"

// Sets default values
ACrystal::ACrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = TriggerVolume;

	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>("CrystalMesh");
	CrystalMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACrystal::OnBeginOverlap);

	if (Indicator)
	{
		Indicator->SetIsCrystalActive(true);
	}
}

// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CrystalMesh->AddWorldRotation(FQuat(FRotator(0,1,0)));
}

void ACrystal::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Hammer = Cast<AHammer>(OtherActor);
	if (Hammer)
	{
		auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player)
		{
			if (Player->GetIsAttacking())
			{
				if (DeathParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetTargetLocation());
				}
				auto temp = GetWorld()->GetAuthGameMode();
				AMappeOppgaveGameModeBase* GameMode = Cast<AMappeOppgaveGameModeBase>(temp);
				if (GameMode)
				{
					GameMode->IncreaseCrystalsDestroyed();
				}
				if (Indicator)
				{
					Indicator->SetIsCrystalActive(false);
				}
				CrystalMesh->SetVisibility(false);
			}
		}
	}
}