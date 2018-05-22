// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

// Forward declarations
class ACrystalIndicator;

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetLastMap(const FName& MapName) { LastMap = MapName; }

	UFUNCTION(BlueprintPure)
	FName GetLastMap() { return LastMap; }

	UFUNCTION(BlueprintPure)
	bool GetMinesMapFinished() { return bMinesMapNotFinished; }
	UFUNCTION(BlueprintPure)
	bool GetPortMapFinished() { return bPortMapNotFinished; }
	void SetMinesMapFinished() { bMinesMapNotFinished = false; }
	void SetPortMapFinished() { bPortMapNotFinished = false; }

	UFUNCTION(BlueprintPure)
	bool GetIntroVideoHasPlayed() { return bIntroVideoHasPlayed; }
	UFUNCTION(BlueprintPure)
	bool GetEndVideoHasPlayed() { return bEndVideoHasPlayed; }
	UFUNCTION(BlueprintCallable)
	void SetIntroVideoHasPlayed() { bIntroVideoHasPlayed = true; }
	UFUNCTION(BlueprintCallable)
	void SetEndVideoHasPlayed() { bEndVideoHasPlayed = true; }

private:
	FName LastMap = "";

	bool bMinesMapNotFinished = true;
	bool bPortMapNotFinished = true;
	bool bIntroVideoHasPlayed = false;
	bool bEndVideoHasPlayed = false;
};
