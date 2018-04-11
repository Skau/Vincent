// Fill out your copyright notice in the Description page of Project Settings.

#include "BombRoller.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

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

void ABombRoller::Explode()
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 2, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(),TArray<AActor*>());

	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), GetActorRotation(), FVector(2));
	}

	Destroy();
}

float ABombRoller::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	if (!bHasTakenDamageRecently)
	{
		Health -= DamageAmount;

		Knockback(DamageCauser);

		bHasTakenDamageRecently = true;
		GetWorld()->GetTimerManager().SetTimer(TH_HasTakenDamageTimer, this, &ABombRoller::ResetHasTakenDamageTimer, 0.1f);
	}
	return DamageAmount;
}

