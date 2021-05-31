// Fill out your copyright notice in the Description page of Project Settings.

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TrunkMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *BoxCollision;

};