// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMath.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	RootComponent = TriggerVolume;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlatformMesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	TotalDistanceToTravel = FVector::DotProduct((GlobalTargetLocation - GetActorLocation()), (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal());

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMovingPlatform::OnBeginOverlap);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActive)
	{
		if (bLerpMove)
		{
			LerpMove(DeltaTime);
		}
		else
		{
			Move(DeltaTime);
		}
	}
}

void AMovingPlatform::LerpMove(float DeltaTime)
{
	FVector Location = GetActorLocation();
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	auto DistanceLeftToTravel = FVector::DotProduct((GlobalTargetLocation - Location), Direction);
	auto DistanceFromStartLocation = TotalDistanceToTravel - DistanceLeftToTravel;
	auto alpha = UKismetMathLibrary::NormalizeToRange(DistanceFromStartLocation, 0, TotalDistanceToTravel);

	SetActorLocation(FMath::VInterpTo(Location, GlobalTargetLocation, DeltaTime, alpha + SpeedConstant));

	if (DistanceLeftToTravel < 0.3f)
	{
		SwapDirection();
	}
}

void AMovingPlatform::Move(float DeltaTime)
{
	FVector Location = GetActorLocation();
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	auto DistanceLeftToTravel = FVector::DotProduct((GlobalTargetLocation - Location), Direction);
	if (DistanceLeftToTravel < 0.3f)
	{
		if (!bTimerSet)
		{
			UE_LOG(LogTemp, Warning, TEXT("Timer started"))
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
	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

	FVector Swap = GlobalStartLocation;
	GlobalStartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Swap;

	TotalDistanceToTravel = FVector::DotProduct((GlobalTargetLocation - GetActorLocation()), (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal());

	bTimerSet = false;
}

void AMovingPlatform::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bIsActive = true;
}