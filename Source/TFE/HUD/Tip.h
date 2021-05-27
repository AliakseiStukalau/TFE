// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tip.generated.h"

UENUM()
enum class TipId : uint8
{
    None = 0 UMETA(DisplayName = "None"),
    GetAxe = 1 UMETA(DisplayName = "GetAxe"),
    Grab = 2 UMETA(DisplayName = "Grab")
};

UCLASS()
class TFE_API UTip : public UObject
{
	GENERATED_BODY()

public:
    UTip() { };
    UTip(FText text, TipId id) : TipText(text), Id(id) {}

    TipId GetId() { return Id; }
    FText GetText() { return TipText; }

protected:
    FText TipText;

    TipId Id;
};
