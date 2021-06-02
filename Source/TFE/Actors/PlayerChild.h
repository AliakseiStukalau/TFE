#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireplace.h"
#include "PlayerChild.generated.h"

UCLASS()
class TFE_API APlayerChild : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APlayerChild();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void InitFireplace();

    UFUNCTION()
    void CalcHitPointsDelta();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* ChildMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HitPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HitPointsChangePerSecond;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AFireplace* Fireplace;
};
