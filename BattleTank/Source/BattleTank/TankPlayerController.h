// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

private:

	FVector2D ScreenLocation;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetAimDirection(FVector2D ScreenLocation, FVector& OutAimDirection) const;

	bool GetAimVectorHitLocation(FVector AimDirection, FVector& HitLocation) const;
};
