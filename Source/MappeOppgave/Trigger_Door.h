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

	virtual void Tick(float DeltaTime) override;
	void CheckActors();
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//TODO make it so that this is just a door pointer?
	UPROPERTY(EditAnywhere)
	AActor* Door = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UBoxComponent* TriggerVolume = nullptr;

	TArray<AActor*> OverlappingActors;
	
};
