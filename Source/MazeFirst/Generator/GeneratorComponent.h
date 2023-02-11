// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneratorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEFIRST_API UGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGeneratorComponent();

protected:
	virtual void BeginPlay() override;
};
