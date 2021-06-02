#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Axe.generated.h"

UCLASS()
class TFE_API AAxe : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAxe();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCapsuleComponent* TriggerCapsule;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USceneComponent* Scene;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AxeMesh0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AxeMesh1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AxeMesh2;
};
