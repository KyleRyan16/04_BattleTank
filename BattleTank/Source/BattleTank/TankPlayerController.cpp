// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid tank is being possessed by player"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Reporting for Duty"), *GetControlledTank()->GetName());
	}

}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	AimTowardsCrosshair();
}

	


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location if lintrace through crosshaird
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}
