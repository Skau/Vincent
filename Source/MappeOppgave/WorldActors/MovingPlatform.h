// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class MAPPEOPPGAVE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private: 
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	bool bIsActive = true;

	UPROPERTY(EditAnywhere)
	bool bLerpMove = true;

	UPROPERTY(EditAnywhere)
	float ReturnDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float Velocity = 500.f;

	bool bTimerSet = false;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "1.0"))
	float SpeedConstant = 0.5;

	void LerpMove(float DeltaTime);
	void Move(float DeltaTime);

	void SwapDirection();

	FTimerHandle TH_SwapDelay;

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	float TotalDistanceToTravel;
	
};
