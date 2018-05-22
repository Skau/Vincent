// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger_Teleporter.generated.h"

UENUM()
enum class ETeleportToMap
{
	None,
	Hub,
	Port,
	Mines,
	Tutorial
};

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
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OpenNewMapWithLoading(const FName& MapToLoad);

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UStaticMeshComponent* GetDoorMesh() { return DoorMesh; }

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoorFirstTime();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseDoor();

	UFUNCTION(BlueprintCallable)
	void TeleportPlayer();

	UPROPERTY(EditAnywhere)
	bool bPlayerStartsInside = false;

	UPROPERTY(BlueprintReadWrite)
	bool bPlayerIsInside = false;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* TeleportSound = nullptr;

	UPROPERTY(EditAnywhere)
	ETeleportToMap TeleportToMap = ETeleportToMap::None;

	class APlayerCharacter* Player = nullptr;

	class UCustomGameInstance* GameInstance = nullptr;


};
