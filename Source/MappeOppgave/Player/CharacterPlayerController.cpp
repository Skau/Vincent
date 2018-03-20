// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

ACharacterPlayerController::ACharacterPlayerController(const FObjectInitializer & ObjectInitializer)
	: APlayerController()
{
}

void ACharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(GetPawn());
	bShowMouseCursor = true;
}

void ACharacterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		// Movement bindings
		InputComponent->BindAxis("MoveForward", this, &ACharacterPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ACharacterPlayerController::MoveRight);

		// Action bindings
		InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterPlayerController::Jump);
		InputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterPlayerController::ToggleCrouch);
		InputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterPlayerController::ToggleCrouch);
		InputComponent->BindAction("ToggleHammer", IE_Pressed, this, &ACharacterPlayerController::ToggleHammer);
		InputComponent->BindAction("RegularAttack", IE_Pressed, this, &ACharacterPlayerController::RegularAttack);
		InputComponent->BindAction("Pause", IE_Pressed, this, &ACharacterPlayerController::PauseGame);
		InputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacterPlayerController::SprintOn);
		InputComponent->BindAction("Sprint", IE_Released, this, &ACharacterPlayerController::SprintOff);
	}
}

void ACharacterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!APlayerController::IsPaused() && !bIsSequencePlaying)
	{
		RotateToCursor();
	}
}

void ACharacterPlayerController::RotateToCursor()
{
	if (Player != nullptr)
	{
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		auto Intersection = FMath::LinePlaneIntersection(WorldLocation, WorldLocation + (WorldDirection * 50000), Player->GetActorLocation(), FVector(0, 0, 1));
		auto NewYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), Intersection).Yaw;
		FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
		Player->GetCapsuleComponent()->SetWorldRotation(TargetRotation);
	}
}

void ACharacterPlayerController::MoveForward(float Value)
{
	if (Player != nullptr && Value != 0.0f && !bIsSequencePlaying)
	{
		Player->AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACharacterPlayerController::MoveRight(float Value)
{
	if (Player != nullptr && Value != 0.0f && !bIsSequencePlaying)
	{
		Player->AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACharacterPlayerController::Jump()
{
	if (bIsSequencePlaying || !Player) { return; }

	if (!Player->bIsHoldingHammer)
	{
		Player->Jump();
	}
}

void ACharacterPlayerController::SprintOn()
{
	if (bIsSequencePlaying || !Player) { return; }


	if (!Player->GetIsSprinting())
	{
		if (!Player->getIsHoldingHammer())
		{
			Player->SetMovementSpeed(800);
			Player->bIsSprinting = true;
		}
	}
}

void ACharacterPlayerController::SprintOff()
{
	if (bIsSequencePlaying || !Player) { return; }

	Player->SetMovementSpeed(400);
	Player->bIsSprinting = false;
}

void ACharacterPlayerController::ToggleCrouch()
{
	if (bIsSequencePlaying || !Player) { return; }

	if (Player->CanCrouch())
	{
		Player->Crouch();
	}
	else
	{
		Player->UnCrouch();
	}
}

void ACharacterPlayerController::ToggleHammer()
{
	if (bIsSequencePlaying || !Player) { return; }

	if (Player->getIsHoldingHammer())
	{
		Player->WhenDroppingHammer();
	}
	else
	{
		Player->WhenPickingUpHammer();
	}
}

void ACharacterPlayerController::RegularAttack()
{
	if (bIsSequencePlaying || !Player) { return; }

	Player->Attack();
}

void ACharacterPlayerController::PauseGame()
{
	if (!bIsSequencePlaying)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

