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
	// Sets default values for this pawn's properties
	ATurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite)
	float TurnRate;

	UPROPERTY(EditAnywhere, Category = "Movement", BlueprintReadWrite)
	float FireRange;

	class ATank* Tank;
};