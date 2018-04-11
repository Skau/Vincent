// Fill out your copyright notice in the Description page of Project Settings.

#include "CoalRoller.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ACoalRoller::ACoalRoller()
{
	PrimaryActorTick.bCanEverTick = true;

	Health = 1;
}

void ACoalRoller::BeginPlay()
{
	Super::BeginPlay();

}

void ACoalRoller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

float ACoalRoller::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (!bHasTakenDamageRecently)
	{
		Health -= DamageAmount;

		if (Health <= 0)
		{
			if (DeathParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation(), FVector(2));
			}
			Destroy();
		}

		Knockback(DamageCauser);

		bHasTakenDamageRecently = true;
		GetWorld()->GetTimerManager().SetTimer(TH_HasTakenDamageTimer, this, &ACoalRoller::ResetHasTakenDamageTimer, 0.1f);
	}
	return DamageAmount;
}