// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

#include "Hammer.h"
#include "EnemyChar.h"

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

	// Enables crouching
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

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
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Makes sure the jump height is correct depending on if the hammer is held or not
	SetCorrectJumpHeight();
}

void APlayerCharacter::SetCorrectMovementSpeed(bool Value)
{
	if (Value)
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed / 2;
	}
}

void APlayerCharacter::SetCorrectJumpHeight()
{
	if (bIsHoldingHammer)
	{
		GetCharacterMovement()->JumpZVelocity = LowJump;
	}
	else
	{
		GetCharacterMovement()->JumpZVelocity = HighJump;
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (!bIsHoldingHammer)
		{
			if (OtherActor->IsA(AHammer::StaticClass()))
			{
				bIsCloseEnough = true;
			}
		}
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (!bIsHoldingHammer)
		{
			if (OtherActor->IsA(AHammer::StaticClass()))
			{
				bIsCloseEnough = false;
			}
		}
	}
}

void APlayerCharacter::WhenDroppingHammer()
{
	if (Hammer != nullptr && !GetCharacterMovement()->IsFalling()) 
	{ 
		bIsHoldingHammer = false;
		Hammer->OnDropped();
	}

}

void APlayerCharacter::WhenPickingUpHammer()
{
	if (bIsCloseEnough && !bIsHoldingHammer)
	{
		if (OldHammer == nullptr)
		{
			OldHammer = Hammer;
		}
		OldHammer->Destroy();
		OldHammer = nullptr;

		Hammer = GetWorld()->SpawnActor<AHammer>(HammerBP);
		Hammer->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		bIsHoldingHammer = true;

		Hammer->SetPhysics(false);
	}
}

void APlayerCharacter::Attack()
{
	if (bIsHoldingHammer)
	{
		Hammer->SetAttacking(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT HOLDING HAMMER"))
	}
}