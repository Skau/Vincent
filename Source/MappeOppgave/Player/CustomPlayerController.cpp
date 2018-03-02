// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "PlayerCharacter.h"

ACustomPlayerController::ACustomPlayerController(const FObjectInitializer & ObjectInitializer)
	: APlayerController()
{
}

void ACustomPlayerController::BeginPlay()
{
	Player = Cast<APlayerCharacter>(GetCharacter());
	bShowMouseCursor = true;
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
		InputComponent->BindAction("ToggleHammer", IE_Released, this, &ACustomPlayerController::ToggleHammer);
		InputComponent->BindAction("RegularAttack", IE_Released, this, &ACustomPlayerController::RegularAttack);
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
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		auto Intersection = FMath::LinePlaneIntersection(WorldLocation, WorldLocation + (WorldDirection*50000), Player->GetActorLocation(), FVector(0,0,1));
		auto NewYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), Intersection).Yaw;
		FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
		Player->GetCapsuleComponent()->SetWorldRotation(TargetRotation);

		//FHitResult CursorHit;
		//bShowMouseCursor = true;
		//GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), true, OUT CursorHit);
		//if (CursorHit.bBlockingHit)
		//{
		//	auto NewYaw = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), CursorHit.Location).Yaw;
		//	FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
		//	Player->GetCapsuleComponent()->SetWorldRotation(TargetRotation);
		//}
	}
}

void ACustomPlayerController::MoveForward(float Value)
{
	if (Player != nullptr && Value != 0.0f)
	{
		Player->AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACustomPlayerController::MoveRight(float Value)
{
	if (Player != nullptr && Value != 0.0f)
	{
		Player->AddMovementInput(GetActorRightVector(), Value);
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

void ACustomPlayerController::ToggleHammer()
{

	if (Player == nullptr) { return; }

	if (Player->getIsHoldingHammer())
	{
		Player->WhenDroppingHammer();
	}
	else
	{
		Player->WhenPickingUpHammer();
	}
}

void ACustomPlayerController::RegularAttack()
{
	if (Player != nullptr)
	{
		Player->Attack();
	}
}
