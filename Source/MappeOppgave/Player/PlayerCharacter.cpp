// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Hammer.h"
#include "Enemies/CoalRoller.h"
#include "Enemies/EnemyChar.h"

#define OUT
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// To enable overlap events
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	// Creates the camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 900.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->SetWorldRotation(FRotator(-50.0f, 0.f, 0.f));

	// Creates the camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Properly alignes mesh with capsule component
	GetMesh()->RelativeRotation = FRotator(0, -90, 0);
	GetMesh()->RelativeLocation = FVector(0, 0, -80);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// set up a notification for when this component overlaps something  
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	// set up a notification for when this component is no longer overlapping something  
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);

	NormalSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SprintSpeed = GetCharacterMovement()->MaxCustomMovementSpeed;

	SpawnLocation = GetActorLocation();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		bIsDead = true;
		WhenDroppingHammer();
	}

	if (bIsHoldingHammer)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	}

	if (GetActorLocation().Z < -2000)
	{
		SetActorLocation(SpawnLocation);
	}
	// If sprinting and the player picks up hammer, stop sprinting
	if (bIsSprinting)
	{
		if (bIsHoldingHammer)
		{
			bIsSprinting = false;
			SetMovementSpeed(NormalSpeed);
		}
	}
}

void APlayerCharacter::SetMovementSpeed(int Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value;
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AHammer::StaticClass()))
	{
		if (!bIsHoldingHammer)
		{
			bIsCloseEnough = true;
		}
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AHammer::StaticClass()))
	{
		if (!bIsHoldingHammer)
		{
			bIsCloseEnough = false;
		}
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (!bHasBeenHitRecently)
	{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

		Health -= DamageAmount;

		if (Health > 0)
		{
			// Runs BP timeline
			Knockback(DamageCauser, EnemyHitForwardVector);

			bHasBeenHitRecently = true;
			GetWorld()->GetTimerManager().SetTimer(TH_HasBeenHitRecentlyTimer, this, &APlayerCharacter::ResetHasBeenHitTimer, 0.5f);
		}
	}

	if (Health <= 0)
	{
		bIsDead = true;
		WhenDroppingHammer();
	}

	return DamageAmount;
}

void APlayerCharacter::WhenDroppingHammer()
{
	if (!Hammer) { return; }

	if (bIsHoldingHammer && !GetCharacterMovement()->IsFalling()) 
	{ 
		Hammer->OnDropped();
		bIsHoldingHammer = false;
	}
}

void APlayerCharacter::WhenPickingUpHammer()
{

	if (!Hammer) { UE_LOG(LogTemp, Warning, TEXT("Hammer not found")) return; }

	if (bIsCloseEnough && !bIsHoldingHammer)
	{
		Hammer->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Hammer->OnPickedUp();
		Hammer->SetActorRelativeRotation(FRotator(0));
		bIsHoldingHammer = true;
	}
}