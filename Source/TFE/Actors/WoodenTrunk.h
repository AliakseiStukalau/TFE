#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WoodenTrunk.generated.h"


UCLASS()
class TFE_API AWoodenTrunk : public AActor
{
    GENERATED_BODY()

public:

    // Sets default values for this actor's properties
    AWoodenTrunk();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TrunkMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UBoxComponent* BoxCollision;
};
