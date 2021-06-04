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


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* ChildMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AFireplace* Fireplace;

    float HitPoints;
    float HitPointsChangePerSecond;
};
