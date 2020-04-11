// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheeel.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheeel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheeel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void SetupConstraints() const;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPhysicsConstraintComponent* MassToAxlePhysics = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPhysicsConstraintComponent* AxleToWheelPhysics = nullptr;

};
