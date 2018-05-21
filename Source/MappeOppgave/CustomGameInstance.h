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

	bool GetMinesMapFinished() { return bMinesMapNotFinished; }
	bool GetPortMapFinished() { return bPortMapNotFinished; }
	void SetMinesMapFinished() { bMinesMapNotFinished = false; }
	void SetPortMapFinished() { bPortMapNotFinished = false; }

private:
	FName LastMap = "";

	bool bMinesMapNotFinished = true;
	bool bPortMapNotFinished = true;
};
