// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

UCLASS()
class MAZEFIRST_API AMenuController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
