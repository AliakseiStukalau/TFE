#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Ghost.generated.h"

UCLASS()
class TFE_API AGhost : public ACharacter
{
    GENERATED_BODY()

public:

    AGhost();

    UFUNCTION()
    void OnTargetPerceptionUpd(AActor* Actor, FAIStimulus Stimulus);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UParticleSystemComponent* SmokePS;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* GhostHeadMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UAIPerceptionComponent* AIPerception;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UAISenseConfig_Sight* AISightConfig;

    UPROPERTY()
    UBlackboardComponent* Blackboard;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float PursuitRadius;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float WalkRadius;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    bool IsPlayerDetected;

    FVector InitialLocation;

    float AttackMovementSpeed;
    float UsualMovementSpeed;
};
