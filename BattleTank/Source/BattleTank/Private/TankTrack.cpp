// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheeel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Find speed at which tank is slipping sideways
}

TArray<ASprungWheeel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheeel*> Result;
		
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
		for (USceneComponent* Child : Children)
		{
			auto SpawnPoint = Cast<USpawnPoint>(Child);
			if (!SpawnPoint) { continue; }
			auto Wheel = Cast<ASprungWheeel>(SpawnPoint->GetSpawnedActor());
			if (!Wheel) { continue; }
			Result.Add(Wheel);	
		}
	return Result;
}


void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);	
	DriveTrack(CurrentThrottle);
}
void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}
