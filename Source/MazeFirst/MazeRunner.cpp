// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeRunner.h"
#include "EnhancedInputSubsystems.h"
#include "MazeFirstGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"

AMazeRunner::AMazeRunner()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(GetCapsuleComponent());
    CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    CameraComponent->bUsePawnControlRotation = true;
}

void AMazeRunner::BeginPlay()
{
    Super::BeginPlay();
    bHelpVisible = false;
    if (const auto PlayerController = Cast<APlayerController>(Controller))
    {
        if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MappingContext, 0);
        }
    }
}

void AMazeRunner::ShowHelp()
{
    bHelpVisible ^= true;
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->ShowHelpPath.Broadcast(bHelpVisible);
    }
}

void AMazeRunner::GenerateMaze()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->GenerateNewMaze.Broadcast();
        GameMode->ResetPlayer(GetController());
    }
    bHelpVisible = false;
}

void AMazeRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMazeRunner::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMazeRunner::Look);
        EnhancedInputComponent->BindAction(HelpAction, ETriggerEvent::Triggered, this, &AMazeRunner::ShowHelp);
        EnhancedInputComponent->BindAction(GenerateNewMazeAction, ETriggerEvent::Triggered, this, &AMazeRunner::GenerateMaze);
    }
}

void AMazeRunner::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void AMazeRunner::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}
