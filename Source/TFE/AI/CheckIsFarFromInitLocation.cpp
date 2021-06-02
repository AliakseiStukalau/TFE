// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckIsFarFromInitLocation.h"
#include "../Actors/Ghost.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UCheckIsFarFromInitLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* pBlackboard = OwnerComp.GetBlackboardComponent();
    AGhost *pGhost = Cast<AGhost>(OwnerComp.GetAIOwner()->GetPawn());

    if(pGhost && pBlackboard)
    {
        const float distance = (pGhost->GetActorLocation() - pBlackboard->GetValueAsVector(InitialLocation.SelectedKeyName)).Size();

        if (pBlackboard->GetValueAsBool(CanSeePlayerKey.SelectedKeyName))
        {
            if (distance > pGhost->PursuitRadius)
            {
                pBlackboard->SetValueAsBool(IsTooFarFromInitLocationKey.SelectedKeyName, true);
                pBlackboard->SetValueAsBool(CanSeePlayerKey.SelectedKeyName, true);
            }
            else
                return EBTNodeResult::Type::Succeeded;
        }
        else
        {
            if (distance > pGhost->WalkRadius)
            {
                pBlackboard->SetValueAsBool(IsTooFarFromInitLocationKey.SelectedKeyName, true);
                pBlackboard->SetValueAsBool(CanSeePlayerKey.SelectedKeyName, true);
            }
            else
                return EBTNodeResult::Type::Succeeded;
        }
    }

    return EBTNodeResult::Type::Succeeded;
}
