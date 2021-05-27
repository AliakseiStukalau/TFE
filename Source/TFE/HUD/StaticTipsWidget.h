// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "StaticTipsWidget.generated.h"

/**
 * 
 */
UCLASS()
class TFE_API UStaticTipsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UStaticTipsWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TipTB1;
};
