// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMath.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	TotalDistanceToTravel = FVector::DotProduct((GlobalTargetLocation - GetActorLocation()), (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal());
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActive)
	{
		Move(DeltaTime);
	}
}

void AMovingPlatform::Move(float DeltaTime)
{
	FVector Location = GetActorLocation();
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	auto DistanceLeftToTravel = FVector::DotProduct((GlobalTargetLocation - Location), Direction);
	auto DistanceFromStartLocation = TotalDistanceToTravel - DistanceLeftToTravel;
	auto alpha = UKismetMathLibrary::NormalizeToRange(DistanceFromStartLocation, 0, TotalDistanceToTravel);

	SetActorLocation(FMath::VInterpTo(Location, GlobalTargetLocation, DeltaTime, alpha + SpeedConstant), true);

	if (DistanceLeftToTravel < 0.3f)
	{
		SwapDirection();
	}
}

void AMovingPlatform::SwapDirection()
{
	FVector Location = GetActorLocation();
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	FVector Swap = GlobalStartLocation;
	GlobalStartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Swap;

	TotalDistanceToTravel = FVector::DotProduct((GlobalTargetLocation - GetActorLocation()), (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal());
}

