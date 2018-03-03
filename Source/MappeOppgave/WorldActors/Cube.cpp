// Fill out your copyright notice in the Description page of Project Settings.

#include "Cube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

