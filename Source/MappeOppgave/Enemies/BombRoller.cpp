// Fill out your copyright notice in the Description page of Project Settings.

#include "BombRoller.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"

ABombRoller::ABombRoller()
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>("Explosion Force");
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

	Destroy();
}


