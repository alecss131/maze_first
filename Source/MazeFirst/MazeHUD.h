// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MazeHUD.generated.h"

class UUserWidget;

UCLASS()
class MAZEFIRST_API AMazeHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> HudWidgetClass;

private:
    UPROPERTY()
    UUserWidget* PauseWidget;

    UPROPERTY()
    UUserWidget* HudWidget;

    UFUNCTION()
    void OnSetPause(bool Paused);
};
