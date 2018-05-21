// Fill out your copyright notice in the Description page of Project Settings.

#include "MappeOppgaveGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"
#include "WorldActors/CrystalIndicator.h"

void AMappeOppgaveGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == "Port")
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HubAndPortMusic);
		UGameplayStatics::PlaySound2D(GetWorld(), PortAmbient);
	}
	else if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == "Mines3")
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MinesMusic);
		UGameplayStatics::PlaySound2D(GetWorld(), MinesAmbient);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HubAndPortMusic);
	}

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