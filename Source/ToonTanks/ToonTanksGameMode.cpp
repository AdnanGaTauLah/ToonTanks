// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	// Check what type of actor died. If Turret, add to score. If Player -> go to lose condition.
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if (PlayerTank->GetPlayerController())
		{
			PlayerTank->DisableInput(PlayerTank->GetPlayerController());
			PlayerTank->GetPlayerController()->bShowMouseCursor = false;
		}
	}
	else if (ATurret* DestroyedTower = Cast<ATurret>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}