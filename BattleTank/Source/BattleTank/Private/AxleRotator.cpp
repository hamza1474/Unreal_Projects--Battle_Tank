// Fill out your copyright notice in the Description page of Project Settings.


#include "AxleRotator.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime\Engine\Classes\PhysicsEngine\PhysicsConstraintComponent.h"


// Sets default values
AAxleRotator::AAxleRotator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AxleToWheelPhysics = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleToWheelPhysics"));
	SetRootComponent(AxleToWheelPhysics);

	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	Axle->SetupAttachment(AxleToWheelPhysics);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(AxleToWheelPhysics);

}

// Called when the game starts or when spawned
void AAxleRotator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAxleRotator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

