// Fill out your copyright notice in the Description page of Project Settings.

#include "BombRoller.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Gamemodes/MappeOppgaveGameModeBase.h"

ABombRoller::ABombRoller()
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>("Explosion Force");
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Health = 100;
}

void ABombRoller::BeginPlay()
{
	Super::BeginPlay();

}

void ABombRoller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called from AIBT when it should explode
void ABombRoller::Explode()
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(),TArray<AActor*>());

	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), GetActorRotation(), FVector(2));
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	auto GameMode = Cast<AMappeOppgaveGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GameMode->RemoveEnemyFromAllEnemies(this);

	Destroy();
}

float ABombRoller::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (!bHasTakenDamageRecently)
	{
		Health -= DamageAmount;

		// Knockbacks the bombroller if possible.
		// Done via timer so it doesn't happen multiple times per second because of overlap.
		if (!bHasBeenKnockedbackRecently)
		{
			Knockback(DamageCauser);
			bHasBeenKnockedbackRecently = true;
		}

		bHasTakenDamageRecently = true;
		GetWorld()->GetTimerManager().SetTimer(TH_HasTakenDamageTimer, this, &ABombRoller::ResetHasTakenDamageTimer, 0.1f);
	}
	return DamageAmount;
}

