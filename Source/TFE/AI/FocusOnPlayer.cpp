#include "FocusOnPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "../Actors/Ghost.h"

EBTNodeResult::Type UFocusOnPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* aiController = OwnerComp.GetAIOwner();
    if (aiController)
    {
        ACharacter* pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

        if (pPlayer)
            aiController->SetFocus(pPlayer);
    }

    return EBTNodeResult::Type::Succeeded;
}

