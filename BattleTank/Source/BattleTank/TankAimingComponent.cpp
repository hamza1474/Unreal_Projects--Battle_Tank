// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = 5;
	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!ensure(Barrel)) { return; }
	auto isBarrelMoving = !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
	
	if (CurrentAmmo <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (isBarrelMoving)
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(TurretToSet || BarrelToSet)) { return; }
	Turret = TurretToSet;
	Barrel = BarrelToSet;

}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel || Turret)) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")) ;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}

}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (FiringState != EFiringState::Reloading && CurrentAmmo > 0) {
		if (!ensure(Barrel)) { return; }
	
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBluePrint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		if (Projectile)
		{
			CurrentAmmo--;
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return CurrentAmmo;
}

void UTankAimingComponent::MoveBarrel(FVector& AimDir)
{
	if (!ensure(Barrel || Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDir.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) >= 180)
	{
		Turret->RotateTurret(-(360-DeltaRotator.Yaw));
	}
	else
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
}



