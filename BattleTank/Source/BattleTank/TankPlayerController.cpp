// Fill out your copyright notice in the Description page of Project Settings.


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

ATank* ATankPlayerController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

