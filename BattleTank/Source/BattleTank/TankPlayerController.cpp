// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"



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

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // has "side-effect", is going to line trace
	{

		ATank* ThisTank = GetControlledTank();

		ThisTank->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector AimDirection; // Direction the crosshair is aiming at in the world space
	if (GetAimDirection(ScreenLocation, AimDirection))
	{
		// Send line trace along that AimDirection, and see what we hit (up to a max range)
		GetAimVectorHitLocation(AimDirection, OutHitLocation);
		
		return true;
	}

	return false;
}

bool ATankPlayerController::GetAimVectorHitLocation(FVector AimDirection, FVector& HitLocation) const
{

	FHitResult HitResult;
	FTwoVectors TracePoints;


	TracePoints.v1 = PlayerCameraManager->GetCameraLocation();
	TracePoints.v2 =  AimDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TracePoints.v1,
		TracePoints.v2,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // line trace didn't succeed
}

bool ATankPlayerController::GetAimDirection(FVector2D ScreenLocation, FVector& OutAimDirection) const
{
	// "De-project" the screen position of the crosshair to a world direction
	FVector OutAimLocation; // Value not needed, method below requires to function
	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OutAimLocation,
		OutAimDirection
	);
	
}






