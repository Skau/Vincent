// Fill out your copyright notice in the Description page of Project Settings.

#include "Hammer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "EnemyChar.h"
#include "PlayerCharacter.h"

// Sets default values
AHammer::AHammer()
{
	PrimaryActorTick.bCanEverTick = true;


	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));
	RootComponent = HammerMesh;

	HammerMesh->bGenerateOverlapEvents = true;

	bIsDropped = true;
}

// Called when the game starts or when spawned
void AHammer::BeginPlay()
{
	Super::BeginPlay();

	// set up a notification for when this component overlaps something  
	HammerMesh->OnComponentBeginOverlap.AddDynamic(this, &AHammer::OnOverlapBegin);

	if (bIsDropped)
	{
		SetPhysics(true);
	}
}

// Called every frame
void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttacking)
	{
		RayCastFront();
		RayCastBack();
		AddActorLocalRotation(FQuat(FRotator(0.f, 0.f, -360.f)*DeltaTime));
	}
	
	/***TICK IS TURNED ON***/

}

void AHammer::OnDropped()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	SetPhysics(true);
}

void AHammer::SetPhysics(bool Value)
{
	HammerMesh->SetSimulatePhysics(Value);
	HammerMesh->WakeRigidBody();
}

void AHammer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping %s"), *OtherActor->GetName())
	}
}


FHitResult AHammer::RayCastFront()
{
	float traceDistance = 30.f;
	FHitResult CastHit;
	FColor traceColor = FColor::Red;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FVector startVector = HammerMesh->GetSocketLocation("FrontHammer");
	FVector endVector = startVector + (GetActorForwardVector() * traceDistance);

	GetWorld()->LineTraceSingleByChannel(CastHit, startVector, endVector, ECC_Visibility, TraceParameters);

	if (CastHit.bBlockingHit)
	{
		traceColor = FColor::Blue;
		endVector = CastHit.Location;
		auto Destroyable = Cast<AEnemyChar>(CastHit.GetActor());
		if (Destroyable)
		{
			UGameplayStatics::ApplyPointDamage(Destroyable, 1.f, GetActorForwardVector(), CastHit,UGameplayStatics::GetPlayerController(GetWorld(),0),this,UDamageType::StaticClass());
			if (Player)
			{
				//Player->InflictDamage(Destroyable, 1.f, GetActorForwardVector(), CastHit);
			}
		}
	}
	else
	{
		traceColor = FColor::Red;
	}

	/* For debugging purposes */
	//DrawDebugLine(GetWorld(), CastHit.TraceStart, endVector, traceColor, false, 2.f, 0, 10.f);

	return CastHit;
}

FHitResult AHammer::RayCastBack()
{
	float traceDistance = 30.f;
	FHitResult CastHit;
	FColor traceColor = FColor::Red;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FVector startVector = HammerMesh->GetSocketLocation("BackHammer");
	FVector endVector = startVector - (GetActorForwardVector() * traceDistance);

	GetWorld()->LineTraceSingleByChannel(CastHit, startVector, endVector, ECC_Visibility, TraceParameters);

	if (CastHit.bBlockingHit)
	{
		traceColor = FColor::Blue;
		endVector = CastHit.Location;
		auto Destroyable = Cast<AEnemyChar>(CastHit.GetActor());
		if (Destroyable)
		{
			if (Player)
			{
				//Player->InflictDamage(Destroyable, 1.f, GetActorForwardVector(),CastHit);
			}
		}
	}
	else
	{
		traceColor = FColor::Red;
	}

	/* For debugging purposes */
	//DrawDebugLine(GetWorld(), CastHit.TraceStart, endVector, traceColor, false, 2.f, 0, 10.f);

	return CastHit;
}