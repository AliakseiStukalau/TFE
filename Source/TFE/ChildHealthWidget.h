// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerChild.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "ChildHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TFE_API UChildHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UChildHealthWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdatPercent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HealthPercentTxt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthPercentBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerChild* Child;
};
