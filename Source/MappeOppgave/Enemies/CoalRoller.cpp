// Fill out your copyright notice in the Description page of Project Settings.

#include "CoalRoller.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Player/PlayerCharacter.h"
#include "Gamemodes/MappeOppgaveGameModeBase.h"

ACoalRoller::ACoalRoller()
{
	PrimaryActorTick.bCanEverTick = true;

	Health = 1;
}

void ACoalRoller::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ACoalRoller::OnHit);
}

void ACoalRoller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACoalRoller::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Player->SetEnemyHitForwardVector(GetActorForwardVector());
		FHitResult CastHit;
		UGameplayStatics::ApplyPointDamage(
			OtherActor,
			Damage,
			GetActorForwardVector(),
			CastHit, GetController(),
			this,
			UDamageType::StaticClass()
		);
		if (!bHasBeenKnockedbackRecently)
		{
			Knockback(this);
			bHasBeenKnockedbackRecently = true;
		}
	}
}

float ACoalRoller::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0)
	{
		if (DeathParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation(), FVector(2));
		}

		auto GameMode = Cast<AMappeOppgaveGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		GameMode->RemoveEnemyFromAllEnemies(this);

		Destroy();
	}
	
	return DamageAmount;
}