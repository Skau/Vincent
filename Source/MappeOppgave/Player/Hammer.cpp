// Fill out your copyright notice in the Description page of Project Settings.

#include "Hammer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"


#include "Enemies/EnemyChar.h"
#include "PlayerCharacter.h"
#include "Enemies/CrystalProtector.h"
#include "WorldActors/DestructibleProp.h"

// Sets default values
AHammer::AHammer()
{
	PrimaryActorTick.bCanEverTick = true;

	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));
	RootComponent = HammerMesh;

	HammerMesh->bGenerateOverlapEvents = false;
	HammerMesh->WakeRigidBody();
	HammerMesh->SetSimulatePhysics(true);

	CollisionCapsule = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionCapsule"));
	CollisionCapsule->SetupAttachment(HammerMesh);
}

// Called when the game starts or when spawned
void AHammer::BeginPlay()
{
	Super::BeginPlay();

	// set up a notification for when this component overlaps something with the mesh 
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHammer::OnOverlapBegin);		

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Player->SetHammer(this);

	SpawnLocation = GetActorLocation();
}

// Called every frame
void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHammer::OnDropped()
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	SetPhysics(true);
	//HammerMesh->SetWorldScale3D(FVector(1));
}

void AHammer::OnPickedUp()
{
	HammerMesh->SetWorldScale3D(FVector(1));
	SetActorRotation(FRotator(0,90,0));
	SetPhysics(false);
}

void AHammer::SetPhysics(bool Value)
{
	HammerMesh->SetSimulatePhysics(Value);
}

void AHammer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (Player->GetIsAttacking())
		{
			auto EnemyHit = Cast<AEnemyChar>(OtherActor);
			FHitResult CastHit;
			if (EnemyHit)
			{
				UGameplayStatics::ApplyPointDamage(
					EnemyHit,
					1.f,
					GetActorForwardVector(),
					CastHit, UGameplayStatics::GetPlayerController(GetWorld(), 0),
					Player,
					UDamageType::StaticClass()
				);
			}
			else 
			{
				auto CrystalProtectorHit = Cast<ACrystalProtector>(OtherActor);
				if (CrystalProtectorHit)
				{
					UGameplayStatics::ApplyPointDamage(
						CrystalProtectorHit,
						1.f,
						GetActorForwardVector(),
						CastHit, UGameplayStatics::GetPlayerController(GetWorld(), 0),
						Player,
						UDamageType::StaticClass()
					);
				}
				
			}
		}
	}
}

void AHammer::MoveToSpawnLocation()
{
	if (!GetActorLocation().Equals(SpawnLocation, 50))
	{
		SetActorLocation(SpawnLocation); 
		SetActorRotation(FRotator(0));
	}
}
