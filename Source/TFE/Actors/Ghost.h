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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetPerceptionUpd(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* SmokePS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GhostHeadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAISenseConfig_Sight* AISightConfig;

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
