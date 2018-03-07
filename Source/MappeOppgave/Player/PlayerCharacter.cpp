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

#include "Hammer.h"
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


	//Sets up a shadow decal
	/*ShadowDecal = CreateDefaultSubobject<UDecalComponent>("ShadowDecal");
	ShadowDecal->SetupAttachment(RootComponent);
	ShadowDecal->SetMaterial(0, ShadowMaterial);
	ShadowDecal->SetDecalMaterial(ShadowMaterial);

	static ConstructorHelpers::FObjectFinder<UMaterial>DecalMaterialAsset(TEXT("Material'/Game/Materials/ShadowDecal.ShadowDecal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		ShadowDecal->SetDecalMaterial(DecalMaterialAsset.Object);
	}*/
	//ShadowDecal->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	//ShadowDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());


	//ShadowDecal->DecalSize = FVector(20, 20, 20);

	// Crouching Is Disabled!
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

	SpawnLocation = GetActorLocation();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		SetActorLocation(SpawnLocation);
		Health = 3;
	}

	if (GetActorLocation().Z < -2000)
	{
		SetActorLocation(SpawnLocation);
	}

	// Makes sure the jump height is correct depending on if the hammer is held or not
	SetCorrectJumpHeight();

	//ShadowDecal->AddRelativeLocation(FVector(0,0,-1),false);
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
	if (OtherActor->IsA(AHammer::StaticClass()))
	{
		if (!bIsHoldingHammer)
		{
			bIsCloseEnough = true;
			Hammer = Cast<AHammer>(OtherActor);
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
			Hammer = nullptr;
		}
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;

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
	if (!Hammer) { return; }

	if (bIsCloseEnough && !bIsHoldingHammer)
	{
		Hammer->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Hammer->OnPickedUp();
		bIsHoldingHammer = true;
	}
}

void APlayerCharacter::Attack()
{
	if (!Hammer) { return; }

	if (bIsHoldingHammer)
	{
		Hammer->SetIsAttacking(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT HOLDING HAMMER"))
	}
}