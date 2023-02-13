// Copyright Alexey Morozov. All Rights Reserved.

#include "MazeGenerator.h"
#include "GeometryComponent.h"
#include "HelpComponent.h"
#include "GeneratorComponent.h"
#include "MazeFirstGameModeBase.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SetRootComponent(SceneComponent);
    GeometryComponent = CreateDefaultSubobject<UGeometryComponent>(TEXT("GeometryComponent"));
    GeometryComponent->SetupAttachment(SceneComponent);
    HelpComponent = CreateDefaultSubobject<UHelpComponent>(TEXT("HelpComponent"));
    HelpComponent->SetupAttachment(SceneComponent);
    GeneratorComponent = CreateDefaultSubobject<UGeneratorComponent>(TEXT("GeneratorComponent"));
}

void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();
    if (const auto World = GetWorld(); const auto GameMode = Cast<AMazeFirstGameModeBase>(UGameplayStatics::GetGameMode(World)))
    {
        GameMode->ShowHelpPath.AddUObject(HelpComponent, &UHelpComponent::FlipFlopVisibility);
        GameMode->GenerateNewMaze.AddUObject(this, &AMazeGenerator::GenerateMaze);
        GameMode->RestartMaze.AddUObject(HelpComponent, &UHelpComponent::SetShowPath, false);
    }
    HelpComponent->SetActorParameter(this);
    GenerateMaze();
}

void AMazeGenerator::GenerateMaze()
{
    HelpComponent->SetSize(GeometryComponent->GetCellSize());
    ResetMaze();
    GeneratorComponent->Build(Width, Height);
    const auto &Cells = GeneratorComponent->GetCells();
    const auto &End = GeneratorComponent->GetEndLocation();
    GeometryComponent->Build(Cells, End);
    HelpComponent->Build(Cells, End);
}

void AMazeGenerator::ResetMaze()
{
    GeneratorComponent->Reset();
    GeometryComponent->Reset();
    HelpComponent->Reset();
}
