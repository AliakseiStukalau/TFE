#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CheckIsFarFromInitLocation.generated.h"


UCLASS()
class TFE_API UCheckIsFarFromInitLocation : public UBTTask_BlackboardBase
{
    GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, Category = Blackboard)
    struct FBlackboardKeySelector IsTooFarFromInitLocationKey;

    UPROPERTY(EditAnywhere, Category = Blackboard)
    struct FBlackboardKeySelector CanSeePlayerKey;

    UPROPERTY(EditAnywhere, Category = Blackboard)
    struct FBlackboardKeySelector InitialLocation;
};
