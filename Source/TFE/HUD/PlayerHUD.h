#pragma once

#include "CoreMinimal.h"
#include "ChildHealthWidget.h"
#include "TipWidget.h"
#include "LoseWidget.h"
#include "Tip.h"
#include "StaticTipsWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


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
    void ShowTipWidget(UObject* pTip);

    UFUNCTION()
    void HideTipWidget(TipId tipId);

    UFUNCTION()
    void ShowYouLoseWidget(EPlayerLoseCause loseCause);

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> ChildHealthWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> TipWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UStaticTipsWidget> StaticTipsWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ULoseWidget> YouLoseWidgetClass;

private:
    UChildHealthWidget* ChildHealthWidget;
    UTipWidget* TipWidget;
    UStaticTipsWidget* StaticTipsWidget;
    ULoseWidget* YouLoseWidget;

    TipId CurrentTipId;
};
