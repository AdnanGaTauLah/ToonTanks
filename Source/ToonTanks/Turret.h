// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()
	
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:


	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite)
	float FireRange;

	class ATank* Tank;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool bInFireRange();
};
