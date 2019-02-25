// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h" // contains forward declaration of UTankBarrel
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"




// Sets default values
ATank::ATank()
{
	// Currently no need for tick, delegates down to TankAimingComponent.cpp

	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}


void ATank::SetAimingReference(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	TankAimingComponent->SetAimingReference(BarrelToSet, TurretToSet);	// See blueprint for reference.

	Barrel = TankAimingComponent->Barrel;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{
		// Spawn a projectile, at the socket location on barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunceProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}