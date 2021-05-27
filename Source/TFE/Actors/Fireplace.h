#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/EngineTypes.h"
#include "Fireplace.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireChangeDelegate);


UENUM(BlueprintType)
enum class FireIntensityState : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Smoke = 1 UMETA(DisplayName = "Smoke"),
	Low = 2 UMETA(DisplayName = "Low"),
	Middle = 3 UMETA(DisplayName = "Middle"),
	Full = 4 UMETA(DisplayName = "Full")
};


UCLASS()
class TFE_API AFireplace : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AFireplace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DisableEmmiters();

	void ResetFire();

	void SetFullPower();

	void SetMiddlePower();

	void SetLowPower();

	void SetSmoke();

	void DecreaseFire();

	UFUNCTION()
	void OnDropTrunk();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FireplaceMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* ParticleSystemFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FireIntensityState FireState;


	FFireChangeDelegate OnFireChange;
protected:

	FTimerHandle DecreaseFireTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireDecreaseTime;
};
