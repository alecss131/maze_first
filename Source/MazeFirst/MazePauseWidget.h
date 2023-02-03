// Fill out your copyright notice in the Description page of Project Settings.

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
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

private:
    UFUNCTION()
    void ResumeGame();
    UFUNCTION()
    void ExitGame();
};
