// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declaration
class UTankAimingComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation); 

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetAimingReference(UTankBarrel* BarrelToSet, UTankTurret * TurretToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000.f; // TODO find sensible firing speed


	UFUNCTION(BlueprintCallable, Category = Controls)
	void Fire(FVector LaunchVelocity);
	

protected:

	UTankAimingComponent* TankAimingComponent = nullptr; // Inheriting aiming component

private:

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;  
};
