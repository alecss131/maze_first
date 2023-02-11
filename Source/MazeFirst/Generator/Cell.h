// Copyright Alexey Morozov. All Rights Reserved.

#pragma once

#include "Cell.generated.h"

USTRUCT()
struct FCell
{
    GENERATED_USTRUCT_BODY()
    
    uint8 X;
    uint8 Y;
    uint32 Distance = 0;
    bool bHasLeft = true;
    bool bHasBottom = true;
    bool bIsVisited = false;
};
