// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;
class AHammer;
class USkeletalMeshComponent;
class UDecalComponent;

UCLASS()
class MAPPEOPPGAVE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsDead() { return bIsDead; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsJumpButtonPressed() { return bJumpButtonPressed; }

	UFUNCTION(BlueprintCallable)
	bool getIsCloseEnough() { return bIsCloseEnough; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool getIsHoldingHammer() { return bIsHoldingHammer; }

	UFUNCTION(BlueprintCallable)
	int GetHealth() { return Health; }

	UFUNCTION(BlueprintCallable)
	void SetFullHealth() { Health = 3; }

	UFUNCTION(BlueprintCallable)
	void SetToAlive() { bIsDead = false; }

	UFUNCTION(BlueprintCallable)
	void SetBIsCloseEnough(bool Value) { bIsCloseEnough = Value; }

	UFUNCTION(BlueprintCallable)
	void SetNewSpawnPoint(FVector NewSpawn) { SpawnLocation = NewSpawn; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsSprinting() { return bIsSprinting; }
	
	bool GetIsBeingTeleported(){ return bIsBeingTeleported; }

	void SetIsBeingTeleported(bool Value) { bIsBeingTeleported = Value; }

	void IncrementHealth() { Health++; }

	void DecrementHealth() { Health--; }

	void SetMovementSpeed(int Value);

	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool Value) { bIsAttacking = Value; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsAttacking() { return bIsAttacking; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Knockback(AActor* EnemyCauser);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetSpawnLocation() { return SpawnLocation; }

private:
	void SetIsJumpButtonPressed(bool Value) { bJumpButtonPressed = Value; }

	void SetCorrectJumpHeight();

	void WhenDroppingHammer();

	void WhenPickingUpHammer();

	void SetSpawnLocation(FVector Location) { SpawnLocation = Location; }

	UPROPERTY(VisibleAnywhere)
	int Health = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Jump, meta = (AllowPrivateAccess = "true"))
	float LowJump = 600.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Jump, meta = (AllowPrivateAccess = "true"))
	float HighJump = 1000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	AHammer* Hammer = nullptr;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* ShadowDecal = nullptr;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* ShadowMaterial;*/

	FVector SpawnLocation = FVector(0);

	float NormalSpeed;

	bool bJumpButtonPressed;

	bool bIsDead;

	bool bIsCloseEnough = false;

	bool bIsHoldingHammer = false;

	bool bIsSprinting;

	bool bIsBeingTeleported = true;

	bool bIsAttacking = false;

	bool bHasBeenHitRecently = false;

	void ResetHasBeenHitTimer() { bHasBeenHitRecently = false; }

	FTimerHandle TH_HasBeenHitRecentlyTimer;

	friend class ACharacterPlayerController;
};
