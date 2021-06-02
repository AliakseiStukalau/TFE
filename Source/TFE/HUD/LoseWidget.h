// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LoseWidget.generated.h"

UENUM(BlueprintType)
enum class EPlayerLoseCause : uint8
{
	KilledByGhost = 0 UMETA(DisplayName = "KilledByGhost"),
	ChildHasFrozen = 1 UMETA(DisplayName = "ChildHasFrozen")
};

UCLASS()
class TFE_API ULoseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	ULoseWidget(const FObjectInitializer& objectInitializer);

	UFUNCTION()
	void OnRestartClick();

	UFUNCTION()
	void OnQuitClick();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonRestart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonQuit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerLoseCause LoseCause;
};
