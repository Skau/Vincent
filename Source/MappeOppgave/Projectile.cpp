// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

#include "PlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;



	InitialLifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto MoveDirection = FVector(-1.f, 0.f, 0.f);
	auto NewLocation = GetActorLocation() + MoveDirection * 500 * DeltaTime;
	SetActorLocation(NewLocation);

}

void AProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		auto Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			Player->DecrementHealth();
			Destroy();
		}
	}
}

