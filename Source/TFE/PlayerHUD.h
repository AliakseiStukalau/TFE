// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChildHealthWidget.h"
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ChildHealthWidgetClass;

private:
	UChildHealthWidget* ChildHealthWidget;
};
