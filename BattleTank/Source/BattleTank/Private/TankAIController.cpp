// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"






void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Error retrieving tank name!"), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s reporting for AI duty!"), *GetControlledTank()->GetName());
	}
	
	if (!GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI can't find Players possessed pawn"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI has found Player possessing %s"), *GetPlayerTank()->GetName());
	}



}

void ATankAIController::Tick(float DeltaTime)
{

	if (GetPlayerTank())
	{
		ATank* PlayerTank = GetPlayerTank();
		// TODO Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// TODO Fire if ready
	}

	

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn){return nullptr;}
	return Cast<ATank>(PlayerPawn);
}