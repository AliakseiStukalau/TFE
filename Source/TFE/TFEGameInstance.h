// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DifficultyLevel.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "TFEGameInstance.generated.h"




UCLASS()
class TFE_API UTFEGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()
protected:

    UDifficultyLevel* GetDifficultyLevel0() const;
    UDifficultyLevel* GetDifficultyLevel1() const;
    UDifficultyLevel* GetDifficultyLevel2() const;

    UPROPERTY()
    TArray<UDifficultyLevel*> DifficultyLevels;

    UPROPERTY()
    UDifficultyLevel* CurrentDifficultyLevel;
public:

    UTFEGameInstance();

    UFUNCTION()
    void UpdateDifficulty(int newValue);

    UDifficultyLevel* GetCurrentDifficulty();
};
