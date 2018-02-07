// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"

#include "Trigger_Door.h"


// Sets default values
ATrigger_Door::ATrigger_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (TriggerVolume == nullptr) { return; }

	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void ATrigger_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrigger_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckActors();
}

void ATrigger_Door::CheckActors()
{
	float TotalMass = 0;
	TSubclassOf<AActor> Actor;

	GetOverlappingActors(OverlappingActors, Actor);

	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	if (TotalMass >= 10) //TODO make not hardcoded
	{
		if (Door)
		{
			Door->SetActorLocation(FVector(Door->GetActorLocation().X, Door->GetActorLocation().Y, -5000.f));
		}
	}
	else
	{
		if (Door)
		{
			Door->SetActorLocation(FVector(Door->GetActorLocation().X, Door->GetActorLocation().Y, 0.f));
		}
	}
}

void ATrigger_Door::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

