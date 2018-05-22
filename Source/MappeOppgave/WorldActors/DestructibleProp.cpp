// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleProp.h"

float ADestructibleProp::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage( DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	return DamageAmount;
}
