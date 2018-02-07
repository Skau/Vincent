// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyChar.h"


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
	
}

// Called every frame
void AEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

float AEnemyChar::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Lost: %f, Current health: %f"), DamageAmount, Health)
	if (Health <= 0)
	{
		Destroy();
	}
		return DamageAmount;
}