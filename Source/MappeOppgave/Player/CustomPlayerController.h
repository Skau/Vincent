// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAPPEOPPGAVE_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool GetIsSequencePlaying() { return bIsSequencePlaying; }

	UFUNCTION(BlueprintCallable)
	void SetIsSequencePlaying(bool Value) { bIsSequencePlaying = Value; }

private:
	ACustomPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	void RotateToCursor();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Jump();

	void SprintOn();
	void SprintOff();

	void ToggleCrouch();
	
	void ToggleHammer();

	void RegularAttack();

	void PauseGame();

	class APlayerCharacter* Player;

	bool bIsSequencePlaying;
};
