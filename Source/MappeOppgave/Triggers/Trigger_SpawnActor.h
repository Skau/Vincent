// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger_SpawnActor.generated.h"

// Trigger used for spawning actors through connected spawnpoints
UCLASS()
class MAPPEOPPGAVE_API ATrigger_SpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger_SpawnActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TArray<class ASpawnPoint*> Spawnpoints;

	bool bHasSpawned = false;

	void ActivateSpawnpoints();


	


};
