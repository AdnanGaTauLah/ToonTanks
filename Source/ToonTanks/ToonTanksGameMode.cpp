// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "TankController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	// Check what type of actor died. If Turret, add to score. If Player -> go to lose condition.
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if (TankController)
		{
			TankController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATurret* DestroyedTower = Cast<ATurret>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTurrets--;
		if (TargetTurrets == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankController = Cast<ATankController>(UGameplayStatics::GetPlayerController(this, 0));
	
	GameStart();

	if (TankController)
	{
		TankController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(TankController, &ATankController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, GameStartDelay, false);
	}

}

int32 AToonTanksGameMode::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}