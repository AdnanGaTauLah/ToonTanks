// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}


void ATurret::CheckFireCondition()
{
	// Course: This is the function that checks if the turret can fire
	if (Tank == nullptr)
		return;
	if (bInFireRange() && Tank->bAlive)
		Fire();
}

bool ATurret::bInFireRange()
{
	// Copilot: This is the function that checks if the turret is in fire range

	if (Tank)
	{
		float TargetDistance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (TargetDistance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
