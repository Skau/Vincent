// Fill out your copyright notice in the Description page of Project Settings.

#include "MappeOppgaveGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"
#include "WorldActors/CrystalIndicator.h"

void AMappeOppgaveGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(GetWorld(), MusicSound);

	if (GameInstance == nullptr)
	{
		GameInstance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == "Hub")
	{
		TArray<AActor*> OutActors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrystalIndicator::StaticClass(), OutActors);

		for (auto& actor : OutActors)
		{
			auto Indicator = Cast<ACrystalIndicator>(actor);
			if (Indicator->GetConnectedMap() == EConnectedMap::Port)
			{
				Indicator->SetIsCrystalActive(GameInstance->GetPortMapFinished());
			}
			else
			{
				Indicator->SetIsCrystalActive(GameInstance->GetMinesMapFinished());
			}
		}
	}
}