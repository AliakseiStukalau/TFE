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

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UCapsuleComponent* TriggerCapsule;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* AxeMesh0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* AxeMesh1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* AxeMesh2;
};
