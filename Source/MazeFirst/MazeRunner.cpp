// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeRunner.h"

#include "EnhancedInputSubsystems.h"
#include "MazeFirstGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "EnhancedInputComponent.h"

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
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
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
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMazeRunner::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMazeRunner::Look);
        EnhancedInputComponent->BindAction(HelpAction, ETriggerEvent::Triggered, this, &AMazeRunner::ShowHelp);
        EnhancedInputComponent->BindAction(GenerateNewMazeAction, ETriggerEvent::Triggered, this, &AMazeRunner::GenerateMaze);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMazeRunner::PauseGame);
    }
}

void AMazeRunner::PauseGame()
{
    if (const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->SetPause.Broadcast(true);
    }
}

void AMazeRunner::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    if (Controller)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void AMazeRunner::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}
