// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hammer.generated.h"


class UBoxComponent;
class APlayerCharacter;

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

	void Attack(float DeltaTime);

	void OnDropped();

	void OnPickedUp(AActor* ActorThatPickedUp);

	FHitResult RayCast();
	FHitResult CastHit;
	
	void SetPhysics(bool Value);

	void SetAttacking(bool Value) { bIsAttacking = Value; }

	bool IfAttacking() { return bIsAttacking; }
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HammerMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox = nullptr;

	APlayerCharacter* Player;

	FRotator PlayerRotation;

	FVector Direction;

	FTimerHandle TH_ResetKnockback;

	class AEnemyChar* EnemyHit = nullptr;

	void SetHit() { bWasHit = false; }

	bool bWasHit = false;

	bool bIsDropped;

	bool bIsAttacking;
};