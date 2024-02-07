// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "GameFramework/Pawn.h"

void ATankController::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}