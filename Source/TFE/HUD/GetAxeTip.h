// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tip.h"
#include "GetAxeTip.generated.h"

/**
 * 
 */
UCLASS()
class TFE_API UGetAxeTip : public UTip
{
	GENERATED_BODY()
	
public:
	UGetAxeTip();
	UGetAxeTip(FText text) : UTip(text, TipId::GetAxe) {}
};
