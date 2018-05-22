// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger_Door.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ATrigger_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger_Door();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	int NumberOfOverlappingActors;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere)
	class ADoor* Door = nullptr;
};
