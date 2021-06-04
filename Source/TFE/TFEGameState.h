#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TFEGameState.generated.h"


UCLASS()
class TFE_API ATFEGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FDateTime StartPlayTime;
};
