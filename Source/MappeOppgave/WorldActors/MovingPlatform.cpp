// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "TimerManager.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

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

	if (FVector::DotProduct((GlobalTargetLocation - Location), Direction) < 0.0f)
	{
		if (!bTimerSet)
		{
			GetWorld()->GetTimerManager().SetTimer(TH_SwapDelay, this, &AMovingPlatform::SwapDirection, ReturnDelay);
			bTimerSet = true;
		}
	}
	else
	{
		Location += Velocity * DeltaTime * Direction;
		SetActorLocation(Location, true);
	}
}

void AMovingPlatform::SwapDirection()
{
	FVector Location = GetActorLocation();
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	FVector Swap = GlobalStartLocation;
	GlobalStartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Swap;

	bTimerSet = false;
}

