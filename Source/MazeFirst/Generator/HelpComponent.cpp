// Copyright Alexey Morozov. All Rights Reserved.

#include "HelpComponent.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"

UHelpComponent::UHelpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SplineComponent->SetupAttachment(this);
    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(this);
}

void UHelpComponent::Reset()
{
    SplineComponent->ClearSplinePoints();
    SetShowPath(false);
}

void UHelpComponent::Build(const TArray<TArray<FCell>> &Cells, const FIntVector &End)
{
    FIntVector Current = End;
    AddPoint(Current.X, Current.Y);
    while (!Current.IsZero())
    {
        const auto &CurrentCell = Cells[Current.X][Current.Y];
        const auto Distance = CurrentCell.Distance - 1;
        if (Current.X > 0 && !CurrentCell.bHasBottom && Cells[Current.X - 1][Current.Y].Distance == Distance)
        {
            Current.X--;
        }
        else if (Current.Y > 0 && !CurrentCell.bHasLeft && Cells[Current.X][Current.Y - 1].Distance == Distance)
        {
            Current.Y--;
        }
        else if (Current.X < Cells.Num() - 1 && !Cells[Current.X + 1][Current.Y].bHasBottom && Cells[Current.X + 1][Current.Y].Distance == Distance)
        {
            Current.X++;
        }
        else if (Current.Y < Cells[0].Num() - 1 && !Cells[Current.X][Current.Y + 1].bHasLeft && Cells[Current.X][Current.Y + 1].Distance ==
                 Distance)
        {
            Current.Y++;
        }
        else
        {
            break;
        }
        AddPoint(Current.X, Current.Y);
    }
}

void UHelpComponent::SetSize(float Size)
{
    CellSize = Size;
}

void UHelpComponent::SetShowPath(bool bShow)
{
    NiagaraComponent->SetVisibility(bShow, true);
    NiagaraComponent->SetPaused(!bShow);
}

void UHelpComponent::SetActorParameter(AActor* Param)
{
    NiagaraComponent->SetActorParameter(SplineName, Param);
}

void UHelpComponent::FlipFlopVisibility()
{
    const bool bShow = !NiagaraComponent->IsVisible();
    SetShowPath(bShow);
}

void UHelpComponent::BeginPlay()
{
	Super::BeginPlay();
    NiagaraComponent->SetFloatParameter(SpawnRateParameterName, 10.0f);
    NiagaraComponent->SetFloatParameter(LifeTimeParameterName, 50.0f);
    NiagaraComponent->SetColorParameter(ColorParameterName, FLinearColor(0.0f, 0.3f, 0.0f));
}

void UHelpComponent::AddPoint(const uint8 X, const uint8 Y)
{
    const auto Position = FVector((X + 0.5f) * CellSize, (Y + 0.5f) * CellSize, 0.0f);
    SplineComponent->AddSplinePoint(Position, ESplineCoordinateSpace::Local, true);
}
