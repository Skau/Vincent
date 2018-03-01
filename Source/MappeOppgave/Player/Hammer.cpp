// Fill out your copyright notice in the Description page of Project Settings.

#include "Hammer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Enemies/EnemyChar.h"
#include "PlayerCharacter.h"

// Sets default values
AHammer::AHammer()
{
	PrimaryActorTick.bCanEverTick = true;

	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));
	RootComponent = HammerMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->bGenerateOverlapEvents = true;

	HammerMesh->bGenerateOverlapEvents = false;
	HammerMesh->SetSimulatePhysics(true);
	bIsDropped = true;
}

// Called when the game starts or when spawned
void AHammer::BeginPlay()
{
	Super::BeginPlay();

	// set up a notification for when this component overlaps something  
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHammer::OnOverlapBegin);		

	if (bIsDropped)
	{
		SetPhysics(true);
	}
}

// Called every frame
void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Attack(DeltaTime);

	if (bWasHit && EnemyHit)
	{
		EnemyHit->SetActorLocation(EnemyHit->GetActorLocation() + Direction * 1500.f	*DeltaTime);
	}
	/***TICK IS TURNED ON***/

}

void AHammer::Attack(float DeltaTime)
{
	if (bIsAttacking && GetOwner())
	{
		AddActorLocalRotation(FQuat(FRotator(-360.f, 0.f, 0.f)*DeltaTime));
	
		Player->SetCorrectMovementSpeed(false);

		if(HammerMesh->GetRelativeTransform().Rotator().Yaw <= -30.f)
		{
			bIsAttacking = false;
		}
	}

	if (!bIsAttacking && GetOwner())
	{
		PlayerRotation = GetActorRotation();
		SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
		Player->SetCorrectMovementSpeed(true);
	}
}

void AHammer::OnDropped()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	SetPhysics(true);
	SetOwner(nullptr);
}

void AHammer::OnPickedUp(AActor* ActorThatPickedUp)
{
	SetOwner(ActorThatPickedUp);
	SetPhysics(false);
	Player = Cast<APlayerCharacter>(ActorThatPickedUp);
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
		if(!bWasHit && bIsAttacking)
		{
			EnemyHit = Cast<AEnemyChar>(OtherActor);
			UE_LOG(LogTemp, Warning, TEXT("Found other actor: %s"), *OtherActor->GetName());
			if (EnemyHit)
			{
				UGameplayStatics::ApplyPointDamage(
					EnemyHit,
					1.f,
					GetActorForwardVector(),
					CastHit, UGameplayStatics::GetPlayerController(GetWorld(), 0),
					this,
					UDamageType::StaticClass()
				);

				//Finds direction for knockback
				FVector EnemyLocation = FVector(EnemyHit->GetActorLocation().X, EnemyHit->GetActorLocation().Y, 0.f);
				FVector PlayerLocation = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0.f);
				Direction = (EnemyLocation - PlayerLocation).GetSafeNormal();

				bWasHit = true;
				GetWorld()->GetTimerManager().SetTimer(TH_ResetKnockback, this, &AHammer::SetHit, 0.1f);

				bIsAttacking = false;
			}
		}
	}
}