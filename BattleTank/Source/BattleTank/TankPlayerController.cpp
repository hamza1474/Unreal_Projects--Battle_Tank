// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NEW AIMING NOT FOUND"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}


void ATankPlayerController::AimTowardsCrossHair()
{
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(GetPawn() || AimingComponent)) { return; }
	FVector OutHitLocation;
	if (GetSightRayHitLocation(OUT OutHitLocation))
	{
		AimingComponent->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 OutViewPortSize_X, OutViewPortSize_Y;
	GetViewportSize(OUT OutViewPortSize_X, OUT OutViewPortSize_Y);

	auto ScreenLocation = FVector2D(OutViewPortSize_X * CrossHairXLocation, OutViewPortSize_Y * CrossHairYLocation);
	FVector OutLookDirection;
	if (ensure(GetLookDirection(ScreenLocation, OUT OutLookDirection)))
	{
		return GetLookVectorHitLocation(OUT HitLocation, OutLookDirection);
	}
	return false;
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

