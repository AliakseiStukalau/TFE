// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UFindPlayerLocation::UFindPlayerLocation(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
    bNotifyBecomeRelevant = true;
}

void UFindPlayerLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* pBlackboard = OwnerComp.GetBlackboardComponent();

    if (pBlackboard)
    {
        ACharacter* pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (pPlayer)
            pBlackboard->SetValueAsVector(MoveLocationKey.SelectedKeyName, pPlayer->GetActorLocation());
    }

}
