// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Controlled Tank Detected"), *ControlledTank->GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Human player is controlling tank [%s]"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }
	FVector OutHitLocation;
	if (GetSightRayHitLocation(OUT OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 OutViewPortSize_X, OutViewPortSize_Y;
	GetViewportSize(OUT OutViewPortSize_X, OUT OutViewPortSize_Y);

	auto ScreenLocation = FVector2D(OutViewPortSize_X * CrossHairXLocation, OutViewPortSize_Y * CrossHairYLocation);
	FVector OutLookDirection;
	if (GetLookDirection(ScreenLocation, OUT OutLookDirection))
	{
		GetLookVectorHitLocation(OUT HitLocation, OutLookDirection);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector OutWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		OutWorldLocation, 
		OutLookDirection
		);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &OutHitLocation, FVector LookDirection) const
{
	FHitResult OutHitResult;
	auto Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			OutHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		))
	{
		OutHitLocation = OutHitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
	
}

