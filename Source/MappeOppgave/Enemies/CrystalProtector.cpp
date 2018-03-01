// Fill out your copyright notice in the Description page of Project Settings.

#include "CrystalProtector.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

#include "GameModes/MappeOppgaveGameModeBase.h"
#include "Player/PlayerCharacter.h"
#include "Projectile.h"

// Sets default values
ACrystalProtector::ACrystalProtector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = TriggerVolume;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	bCanShoot = true;

}

// Called when the game starts or when spawned
void ACrystalProtector::BeginPlay()
{
	Super::BeginPlay();
	
	auto temp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player = Cast<APlayerCharacter>(temp);

	auto temp2 = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AMappeOppgaveGameModeBase>(temp2);

	if (GameMode)
	{
		VariableMultiplier = (GameMode->GetCrystalsDestroyed() + 1);
	}
}

// Called every frame
void ACrystalProtector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	if (CurrentLocation.Y - PlayerLocation.Y < ShootRange && CurrentLocation.X - PlayerLocation.X < ShootRange)
	{
		bIsActive = true;
	}
	else
	{
		bIsActive = false;
	}

	if (bIsActive)
	{
		Move(DeltaTime);
		Shoot();
	}

	if (GameMode)
	{
		if (VariableMultiplier != (GameMode->GetCrystalsDestroyed() + 1))
		{
			VariableMultiplier = (GameMode->GetCrystalsDestroyed() + 1);

			MoveSpeed = StartMoveSpeed * VariableMultiplier;

			ShootRate = StartShootRate / VariableMultiplier;
		}
	}

}

void ACrystalProtector::Move(float DeltaTime)
{
	if (Player)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector MoveDirection = FVector(0);

		float DeltaYLocation = Player->GetActorLocation().Y - CurrentLocation.Y;

		if (DeltaYLocation > 5.f)
		{
			MoveDirection = FVector(0.f, 1.f, 0.f);
		}
		else if (DeltaYLocation < -5.f)
		{
			MoveDirection = FVector(0.f, -1.f, 0.f);
		}

		FVector NewLocation = CurrentLocation + MoveDirection * MoveSpeed * DeltaTime;
		SetActorLocation(NewLocation, true);
	}
}

void ACrystalProtector::Shoot()
{
	if (bCanShoot && Projectile_BP)
	{
		auto SpawnDirection = FVector(-1, 0, 0);
		auto SpawnRotation = SpawnDirection.Rotation();
		auto SpawnLocation = GetActorLocation() + FVector(-100, 0, 0);

		GetWorld()->SpawnActor<AProjectile>(Projectile_BP, SpawnLocation, SpawnRotation);

		GetWorld()->GetTimerManager().SetTimer(TH_ShootTimer, this, &ACrystalProtector::ResetShootTimer, ShootRate);
		bCanShoot = false;
	}
}

void ACrystalProtector::ResetShootTimer()
{
	bCanShoot = true;
}
