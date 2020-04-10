// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
protected:
	// Called when the game starts or when spawned
	ATank();
	virtual void BeginPlay() override;
	

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	FTankDelegate OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float TankHitpoints = 100.f;
};
