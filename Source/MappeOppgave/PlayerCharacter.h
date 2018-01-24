// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;
class AHammer;
class USkeletalMeshComponent;

UCLASS()
class MAPPEOPPGAVE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USkeletalMeshComponent* CharacterMesh = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AHammer> HammerBP;

private:

	bool bHasHammer = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jump, meta = (AllowPrivateAccess = "true"))
	float LowJump = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jump, meta = (AllowPrivateAccess = "true"))
	float HighJump = 800.f;

	void MoveForward(float value);
	void MoveRight(float value);
	void ToggleJump();
	void ToggleCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	AHammer* Hammer = nullptr;

	FHitResult CastHit;
	FHitResult RayCast();

	void Drop();

	void Attack();
};
