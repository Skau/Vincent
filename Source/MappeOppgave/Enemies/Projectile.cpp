// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Hammer.h"
#include "Player/PlayerCharacter.h"
#include "Enemies/CrystalProtector.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = CollisionSphere;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
	
	InitialLifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Applies damage to PlayerCharacter
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Player->SetEnemyHitForwardVector(GetActorForwardVector());
		FHitResult CastHit;
		UGameplayStatics::ApplyPointDamage(
			OtherActor,
			Damage,
			GetActorForwardVector(),
			CastHit, Player->GetController(),
			this,
			UDamageType::StaticClass()
		);
		
		Destroy();
	}
	// Applies damage to CrystalProtector
	else if (OtherActor->IsA(ACrystalProtector::StaticClass()))
	{
		if (bHasChangedDirection)
		{
			FHitResult CastHit;
			UGameplayStatics::ApplyPointDamage(
				OtherActor,
				Damage,
				GetActorForwardVector(),
				CastHit, Player->GetController(),
				this,
				UDamageType::StaticClass()
			);
			Destroy();
		}
	}
	// Knocksbacks if hit by hammer
	else if (OtherActor->IsA(AHammer::StaticClass()))
	{
		auto Hammer = Cast<AHammer>(OtherActor);
		if (Player->GetIsAttacking() && !bHasChangedDirection)
		{
			MoveDirection = -MoveDirection;
			Speed *= 2;
			bHasChangedDirection = true;
		}
	}
}

