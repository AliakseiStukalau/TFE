#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindPlayerLocation.generated.h"


UCLASS()
class TFE_API UFindPlayerLocation : public UBTService
{
    GENERATED_BODY()

public:

    UFindPlayerLocation(const FObjectInitializer& objectInitializer);

    virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


    UPROPERTY(EditAnywhere, Category = Blackboard)
    struct FBlackboardKeySelector MoveLocationKey;
};
