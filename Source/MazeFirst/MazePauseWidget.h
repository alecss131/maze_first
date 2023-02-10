// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MazePauseWidget.generated.h"

class UButton;

UCLASS()
class MAZEFIRST_API UMazePauseWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

    UPROPERTY(meta = (BindWidget))
    UButton* RestartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* NewMazeButton;
    
    virtual void NativeConstruct() override;
private:
    UFUNCTION()
    void ResumeGame();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void RestartMaze();

    UFUNCTION()
    void NewMaze();
};
