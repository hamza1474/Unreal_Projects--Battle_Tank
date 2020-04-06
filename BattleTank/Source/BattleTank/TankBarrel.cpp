// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp
	(
		RelativeSpeed,
		-1.0f,
		 1.0f
	);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawElevation = FMath::Clamp
	(
		RelativeRotation.Pitch + ElevationChange, 
		MinElevation, 
		MaxElevation
	);
	SetRelativeRotation(FRotator(RawElevation, 0, 0));
}