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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
		float Velocity = 30.f;

	void SetActive(bool Value) { bIsActive = Value; };

private:
	UPROPERTY(EditAnywhere)
	bool bIsActive = true;

	void Move(float DeltaTime);

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	
};
