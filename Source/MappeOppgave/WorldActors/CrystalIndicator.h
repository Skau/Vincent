// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrystalIndicator.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ACrystalIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystalIndicator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsCrystalActive() { return bIsCrystalActive; }

	void SetIsCrystalActive(bool Value) { bIsCrystalActive = Value; }

private:	
	
	UPROPERTY(VisibleAnywhere)
	class UMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* MaterialWhenActive;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* MaterialWhenInactive;
	
	bool bIsCrystalActive = false;
};
