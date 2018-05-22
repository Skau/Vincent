// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hammer.generated.h"

class APlayerCharacter;
class UBoxComponent;

UCLASS()
class MAPPEOPPGAVE_API AHammer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHammer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void MoveToSpawnLocation();

private:
	void OnDropped();

	void OnPickedUp();

	void SetPhysics(bool Value);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionCapsule = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HammerMesh = nullptr;

	APlayerCharacter* Player = nullptr;

	FVector SpawnLocation = FVector(0);

	friend class APlayerCharacter;
};
