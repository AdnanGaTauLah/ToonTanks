// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}	

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
	// Move the tank forward and backward
	FVector DeltaLocation = FVector::ZeroVector;
	float Deltatime = UGameplayStatics::GetRealTimeSeconds(this);
	DeltaLocation.X = Value * MoveSpeed * Deltatime;
	AddActorLocalOffset(DeltaLocation, true);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Turn(float Value)
{
	// Rotate the tank
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float Deltatime = UGameplayStatics::GetRealTimeSeconds(this);
	DeltaRotation.Yaw = Value * TurnRate * Deltatime;
	AddActorLocalRotation(DeltaRotation, true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20, 12, FColor::Green, false, -1.0f);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::Fire()
{
	Super::Fire();

	DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 20, 12, FColor::Red, true, 4.0f);
}