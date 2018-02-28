// Fill out your copyright notice in the Description page of Project Settings.

#include "CrystalIndicator.h"
#include "Components/StaticMeshComponent.h"

#include "Crystal.h"

// Sets default values
ACrystalIndicator::ACrystalIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void ACrystalIndicator::BeginPlay()
{
	Super::BeginPlay();

	//MeshComponent->SetMaterialByName("Materials/M_Hammer", MaterialWhenActive);

}

// Called every frame
void ACrystalIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MeshComponent->SetMaterialByName("Materials/M_Hammer", MaterialWhenInactive);

	if (bIsCrystalActive)
	{
		MeshComponent->SetMaterial(0, MaterialWhenActive);
	}
	else
	{
		MeshComponent->SetMaterial(0, MaterialWhenInactive);
	}
}

