#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoliageTree.generated.h"

UCLASS()
class TFE_API AFoliageTree : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFoliageTree();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    float RespawnTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TreeMesh;

};
