// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger_Checkpoint.generated.h"

UCLASS()
class MAPPEOPPGAVE_API ATrigger_Checkpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger_Checkpoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateCheckpointTakenWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateCheckpointPromptWidget();

	UFUNCTION(BlueprintCallable)
	void SetIsWidgetPlaying(bool value) { bIsWidgetPlaying= value; }

	void ActivateMesh(UStaticMeshComponent* Mesh);
	void DeactivateMesh(UStaticMeshComponent* Mesh);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CheckpointStand = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CheckpointHandle = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;

	class APlayerCharacter* Player = nullptr;

	bool bIsWidgetPlaying = false;

	bool IsCurrentSpawn = false;
};
