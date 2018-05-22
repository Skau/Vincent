// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MAPPEOPPGAVE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetMoveDirection(FVector Direction) { MoveDirection = Direction; }

private:
	UPROPERTY(EditAnywhere)
	float Speed = 700;

	UPROPERTY(EditAnywhere)
	float Damage = 1.f;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphere = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh = nullptr;
	
	class APlayerCharacter* Player = nullptr;

	FVector MoveDirection = FVector(0);

	bool bHasChangedDirection = false;
};
