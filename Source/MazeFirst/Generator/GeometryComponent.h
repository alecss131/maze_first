// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GeometryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEFIRST_API UGeometryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UGeometryComponent();

protected:
	virtual void BeginPlay() override;
};
