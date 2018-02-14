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
	Health = 100;
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
	
	if (bWasHit)
	{
		Player->SetActorLocation(Player->GetActorLocation() + Direction* 1500.f	*DeltaTime);
	}
}

void AEnemyChar::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		if (!bHasAttackedRecently)
		{
			Player->DecrementHealth();
			FVector EnemyLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0.f);
			FVector PlayerLocation = FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, 0.f);
			Direction = (PlayerLocation - EnemyLocation).GetSafeNormal();

			bWasHit = true;
			GetWorld()->GetTimerManager().SetTimer(TH_ResetKnockback, this, &AEnemyChar::SetHit, 0.1f);

			bHasAttackedRecently = true;
			GetWorld()->GetTimerManager().SetTimer(TH_Attack, this, &AEnemyChar::ResetAttackTimer, 2.f);
		}
	}
}

float AEnemyChar::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Lost: %f, Current health: %f"), DamageAmount, Health)
	if (Health <= 0)
	{
		if (DeathParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation(), FVector(2));
		}
		Destroy();
	}
		return DamageAmount;
}