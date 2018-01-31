// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "PlayerCharacter.h"

ACustomPlayerController::ACustomPlayerController(const FObjectInitializer & ObjectInitializer)
	: APlayerController()
{
}

void ACustomPlayerController::BeginPlay()
{
	Player = Cast<APlayerCharacter>(GetCharacter());
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		// Movement bindings
		InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::MoveRight);

		// Action bindings
		InputComponent->BindAction("Jump", IE_Pressed, this, &ACustomPlayerController::Jump);
		InputComponent->BindAction("Crouch", IE_Pressed, this, &ACustomPlayerController::ToggleCrouch);
		InputComponent->BindAction("Crouch", IE_Released, this, &ACustomPlayerController::ToggleCrouch);
		InputComponent->BindAction("DropHammer", IE_Released, this, &ACustomPlayerController::DropHammer);
		InputComponent->BindAction("PickUpHammer", IE_Released, this, &ACustomPlayerController::PickUpHammer);
	}
}

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToCursor();
	
}

void ACustomPlayerController::RotateToCursor()
{
	if (Player != nullptr)
	{
		FHitResult CursorHit;

		bShowMouseCursor = true;
		GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), true, OUT CursorHit);
		auto NewYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), CursorHit.Location).Yaw;
		FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
		Player->GetCapsuleComponent()->SetWorldRotation(TargetRotation);
	}
}

void ACustomPlayerController::MoveForward(float Value)
{
	if (Player != nullptr && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Player->AddMovementInput(Direction, Value);
	}
}

void ACustomPlayerController::MoveRight(float Value)
{
	if (Player != nullptr && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		Player->AddMovementInput(Direction, Value);
	}
}

void ACustomPlayerController::Jump()
{
	if (Player != nullptr)
	{
		Player->Jump();
	}
}

void ACustomPlayerController::ToggleCrouch()
{
	if (Player->CanCrouch())
	{
		Player->Crouch();
	}
	else
	{
		Player->UnCrouch();
	}
}

void ACustomPlayerController::DropHammer()
{
	if (Player != nullptr)
	{
		Player->WhenDroppingHammer();
	}
}

void ACustomPlayerController::PickUpHammer()
{
	if (Player != nullptr)
	{
		Player->WhenPickingUpHammer();
	}
}
