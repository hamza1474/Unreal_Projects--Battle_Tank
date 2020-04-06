// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp
	(
		RelativeSpeed,
		-1.0f,
		1.0f
	);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawRotation, 0));
}