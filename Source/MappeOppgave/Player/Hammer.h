// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hammer.generated.h"

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
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void Attack(float DeltaTime);

	void OnDropped();

	void OnPickedUp();

	void SetPhysics(bool Value);

	void SetIsAttacking(bool Value) { bIsAttacking = Value; }

	bool GetIsAttacking() { return bIsAttacking; }
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HammerMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox = nullptr;

	APlayerCharacter* Player;

	FRotator PlayerRotation;

	FVector Direction;

	FTimerHandle TH_ResetKnockback;

	class AEnemyChar* EnemyHit = nullptr;

	void SetHit() { bWasHit = false; }

	bool bWasHit = false;

	bool bIsDropped;

	bool bIsAttacking;

	friend class APlayerCharacter;
};
