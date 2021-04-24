// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeRunner.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AMazeRunner::AMazeRunner()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	CameraComponent->bUsePawnControlRotation = true;
}

void AMazeRunner::BeginPlay()
{
	Super::BeginPlay();
}

void AMazeRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMazeRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMazeRunner::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMazeRunner::MoveRight);
	PlayerInputComponent->BindAxis("LookTurn", this, &AMazeRunner::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMazeRunner::AddControllerPitchInput);
}

void AMazeRunner::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void AMazeRunner::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}
