// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyChar.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AEnemyChar::AEnemyChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyChar::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AEnemyChar::OnHit);
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyChar::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Player->SetEnemyHitForwardVector(GetActorForwardVector());
		FHitResult CastHit;
		UGameplayStatics::ApplyPointDamage(
			OtherActor,
			1.f,
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