// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Cell.h"
#include "HelpComponent.generated.h"

class USplineComponent;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEFIRST_API UHelpComponent : public USceneComponent
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
    USplineComponent* SplineComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
    UNiagaraComponent* NiagaraComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = Parameters)
    FName SplineName = "spline_path";

    UPROPERTY(EditDefaultsOnly, Category = Parameters)
    FName SpawnRateParameterName = "spawn_rate";

    UPROPERTY(EditDefaultsOnly, Category = Parameters)
    FName LifeTimeParameterName = "lifetime";

    UPROPERTY(EditDefaultsOnly, Category = Parameters)
    FName ColorParameterName = "color";
    
    UPROPERTY()
    float CellSize;

public:	
	UHelpComponent();

    void Reset();
    void Build(const TArray<TArray<FCell>> &Cells, const FIntVector &End);
    void SetSize(float Size);
    void SetActorParameter(AActor *Param);

    UFUNCTION()
    void SetShowPath(bool bShow);

    UFUNCTION()
    void FlipFlopVisibility();

protected:
	virtual void BeginPlay() override;

private:
    void AddPoint(const uint8 X, const uint8 Y);
};
