// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HelpComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEFIRST_API UHelpComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UHelpComponent();

protected:
	virtual void BeginPlay() override;
};
