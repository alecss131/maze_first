// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MazeRunnerController.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class MAZEFIRST_API AMazeRunnerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;

public:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* PauseAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* HelpAction;

private:
    void PauseGame();
    void ShowHelp();

    UFUNCTION()
    void OnSetPause(bool bPaused);

    UFUNCTION()
    void ResetPlayer();
};
