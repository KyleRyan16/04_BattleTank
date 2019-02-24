// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1); // To what degree we are aiming at relative to current rotator

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond;
	auto Rotation = RelativeRotation.Yaw + RotationChange * GetWorld()->DeltaTimeSeconds;

	SetRelativeRotation(FRotator(0, Rotation, 0));

	return;
}
