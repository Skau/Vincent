// Fill out your copyright notice in the Description page of Project Settings.

#include "CrystalProtector.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "PhysicsEngine/RadialForceComponent.h"
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
}

// Called every frame
void ACrystalProtector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector PlayerLocation = Player->GetActorLocation();

	if (GetDistanceTo(Player) < ActiveRange)
	{
		auto DotProduct = FVector::DotProduct((PlayerLocation - CurrentLocation).GetSafeNormal(), GetActorRightVector());
		Move(DeltaTime, DotProduct);
		Shoot();
	}
}

void ACrystalProtector::Move(float DeltaTime, float DotProduct)
{
	FVector CurrentLocation = GetActorLocation();
	FVector MoveDirection = FVector(0);

	if (DotProduct < 0)
	{
		MoveDirection = -GetActorRightVector();
	}
	else
	{
		MoveDirection = GetActorRightVector();
	}

	FVector NewLocation = CurrentLocation + MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation, true);
}

void ACrystalProtector::Shoot()
{
	if (bCanShoot && Projectile_BP)
	{
		auto SpawnDirection = GetActorForwardVector();
		auto SpawnRotation = SpawnDirection.Rotation();
		auto SpawnLocation = GetActorLocation() + SpawnDirection * 100;

		auto proj = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, SpawnLocation, SpawnRotation);
		proj->SetMoveDirection(SpawnDirection);

		GetWorld()->GetTimerManager().SetTimer(TH_ShootTimer, this, &ACrystalProtector::ResetShootTimer, ShootRate);
		bCanShoot = false;
	}
}

void ACrystalProtector::ResetShootTimer()
{
	bCanShoot = true;
}

