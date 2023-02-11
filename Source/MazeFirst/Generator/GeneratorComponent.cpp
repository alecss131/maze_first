// Copyright Alexey Morozov. All Rights Reserved.

#include "Generator/GeneratorComponent.h"

UGeneratorComponent::UGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
}
