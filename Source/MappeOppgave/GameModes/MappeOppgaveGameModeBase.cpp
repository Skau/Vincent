// Fill out your copyright notice in the Description page of Project Settings.

#include "MappeOppgaveGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AMappeOppgaveGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(GetWorld(), MusicSound);
}