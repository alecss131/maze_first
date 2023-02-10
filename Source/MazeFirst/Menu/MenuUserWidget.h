// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

class UButton;

UCLASS()
class MAZEFIRST_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* PlayButton;

    UPROPERTY(EditAnywhere, Category = Game)
    FName LevelName = NAME_None;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnExit();

    UFUNCTION()
    void OnPlay();
};
