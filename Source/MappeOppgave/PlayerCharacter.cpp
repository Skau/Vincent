// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Hammer.h"
#include "DrawDebugHelpers.h"


#define OUT
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 900.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->bInheritYaw = false;
	CameraBoom->SetWorldRotation(FRotator(-50.0f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent);
	CharacterMesh->RelativeRotation = FRotator(0, -90, 0);
	CharacterMesh->RelativeLocation = FVector(0, 0, -80);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!HammerBP)
	{
		UE_LOG(LogTemp, Error, TEXT("missing hammer_BP"))
		return;
	}
	if (!CharacterMesh) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("missing Character mesh"))
		return; 
	}
	Hammer = GetWorld()->SpawnActor<AHammer>(HammerBP);
	Hammer->AttachToComponent(CharacterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FHitResult CursorHit;

	PC->bShowMouseCursor = true;
	PC->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, OUT CursorHit);

	auto NewYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CursorHit.Location).Yaw;
	FRotator TargetRotation = FRotator(0.f, NewYaw, 0.f);
	GetCapsuleComponent()->SetWorldRotation(TargetRotation);

	CastHit = RayCast();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent)

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("ToggleJump", IE_Pressed, this, &APlayerCharacter::ToggleJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("DropHammer", IE_Released, this, &APlayerCharacter::Drop);
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::ToggleJump()
{
	bHasHammer = !bHasHammer;

	if (bHasHammer)
		GetCharacterMovement()->JumpZVelocity = LowJump;
	else
		GetCharacterMovement()->JumpZVelocity = HighJump;
}

void APlayerCharacter::ToggleCrouch()
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

FHitResult APlayerCharacter::RayCast()
{
	float traceDistance = 300.f;
	FColor traceColor = FColor::Red;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FVector startVector = CharacterMesh->GetComponentLocation() + FVector(0.f, 0.f, 100.f);
	FVector endVector = startVector + (CharacterMesh->GetRightVector() * traceDistance);

	GetWorld()->LineTraceSingleByChannel(CastHit, startVector, endVector, ECC_Visibility, TraceParameters);

	if (CastHit.bBlockingHit)
	{
		traceColor = FColor::Blue;
		endVector = CastHit.Location;
	}
	else
	{
		traceColor = FColor::Red;
	}

	/* For debugging purposes */
	DrawDebugLine(GetWorld(), CastHit.TraceStart, endVector, traceColor, false, 10.f, 0, 10.f);

	return CastHit;

}

void APlayerCharacter::Drop()
{
	Hammer->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld,false));
}

void APlayerCharacter::Attack()
{
}

