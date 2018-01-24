// Fill out your copyright notice in the Description page of Project Settings.

#include "Hammer.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AHammer::AHammer()
{
	PrimaryActorTick.bCanEverTick = false;

	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));
	RootComponent = HammerMesh;
}

// Called when the game starts or when spawned
void AHammer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TICK IS TURNED OFF

}

