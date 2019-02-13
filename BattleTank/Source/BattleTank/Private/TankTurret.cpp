// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond;
	auto Azimuth = RelativeRotation.Yaw + AzimuthChange * GetWorld()->DeltaTimeSeconds;;

	SetRelativeRotation(FRotator(0, Azimuth, 0));

	UE_LOG(LogTemp, Warning, TEXT("%f"), RelativeSpeed);

	return;
}
