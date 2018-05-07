// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleProp.h"

float ADestructibleProp::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage( DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("prop took damage!"))
	return 0.0f;
}
