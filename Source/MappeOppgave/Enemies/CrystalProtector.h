// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrystalProtector.generated.h"

// Forward declarations
class AProjectile;

UCLASS()
class MAPPEOPPGAVE_API ACrystalProtector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystalProtector();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	void Move(float DeltaTime);

	void Shoot();

	void ResetShootTimer();

	UPROPERTY(EditAnywhere)
	float StartMoveSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float StartShootRate = 2.f;

	UPROPERTY(EditAnywhere)
	float ShootRange = 2000.f;

	float MoveSpeed = StartMoveSpeed;
	float ShootRate = StartShootRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> Projectile_BP;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	class APlayerCharacter* Player;

	bool bIsActive;

	bool bCanShoot;


	FTimerHandle TH_ShootTimer;

	class AMappeOppgaveGameModeBase* GameMode = nullptr;

	int VariableMultiplier = 0;

};