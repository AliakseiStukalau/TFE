// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChildHealthWidget.h"
#include "TipWidget.h"
#include "HUD/Tip.h"
#include "HUD/StaticTipsWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class TFE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerHUD();


	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateHealthWidget();

	UFUNCTION()
	void ShowTipWidget(UObject *pTip);

	UFUNCTION()
	void HideTipWidget(TipId tipId);


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ChildHealthWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> TipWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStaticTipsWidget> StaticTipsWidgetClass;

private:
	UChildHealthWidget* ChildHealthWidget;
	UTipWidget* TipWidget;
	UStaticTipsWidget* StaticTipsWidget;

	TipId CurrentTipId;
};
