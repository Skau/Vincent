// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyChar.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Gamemodes/MappeOppgaveGameModeBase.h"
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

	auto GameMode = Cast<AMappeOppgaveGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->AddEnemyToAllEnemies(this);

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SpawnLocation = GetActorLocation();
}

// Called every frame
void AEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

