// Copyright Alexey Morozov. All Rights Reserved.

#include "Generator/GeometryComponent.h"

UGeometryComponent::UGeometryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGeometryComponent::BeginPlay()
{
	Super::BeginPlay();
}
