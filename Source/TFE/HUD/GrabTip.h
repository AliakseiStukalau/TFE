#pragma once

#include "CoreMinimal.h"
#include "Tip.h"
#include "GrabTip.generated.h"


UCLASS()
class TFE_API UGrabTip : public UTip
{
    GENERATED_BODY()

public:
    UGrabTip();
    UGrabTip(FText text) : UTip(text, TipId::Grab) {}
};
