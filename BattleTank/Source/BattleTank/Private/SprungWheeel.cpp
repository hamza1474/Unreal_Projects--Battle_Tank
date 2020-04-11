// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheeel.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime\Engine\Classes\PhysicsEngine\PhysicsConstraintComponent.h"

// Sets default values
ASprungWheeel::ASprungWheeel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassToAxlePhysics = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassToAxlePhysics"));
	SetRootComponent(MassToAxlePhysics);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassToAxlePhysics);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleToWheelPhysics = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleToWheelPhysics"));
	AxleToWheelPhysics->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheeel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraints();
}

// Called every frame
void ASprungWheeel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheeel::SetupConstraints() const
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	UE_LOG(LogTemp, Warning, TEXT("%s is attaching"), *BodyRoot->GetName())
	MassToAxlePhysics->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleToWheelPhysics->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);

}

