// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger_Teleporter.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ATrigger_Teleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger_Teleporter();

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
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	ATrigger_Teleporter* ConnectedTeleporter;
	
};
