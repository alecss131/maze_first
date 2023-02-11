// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MazeHUD.generated.h"

class UUserWidget;
class UMazePauseWidget;

UCLASS()
class MAZEFIRST_API AMazeHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UMazePauseWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    TSubclassOf<UUserWidget> HudWidgetClass;

private:
    UPROPERTY()
    UMazePauseWidget* PauseWidget;

    UPROPERTY()
    UUserWidget* HudWidget;

    UFUNCTION()
    void OnSetPause(bool bPaused);
};
