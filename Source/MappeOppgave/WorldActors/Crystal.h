// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemies/EnemyChar.h"
#include "Crystal.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintPure)
	bool GetIsActive() { return bIsActive; }

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CrystalMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* InnerRing = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OuterRing = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Pedestal = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathParticle = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ShatterSound = nullptr;

	bool bIsActive = true;


};
