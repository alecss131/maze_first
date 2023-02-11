// Copyright Alexey Morozov. All Rights Reserved.

#include "Generator/HelpComponent.h"

UHelpComponent::UHelpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHelpComponent::BeginPlay()
{
	Super::BeginPlay();
}
