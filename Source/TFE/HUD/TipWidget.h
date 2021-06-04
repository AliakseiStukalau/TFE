#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "TipWidget.generated.h"


UCLASS()
class TFE_API UTipWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UTipWidget(const FObjectInitializer& objectInitializer);

    virtual void NativeConstruct() override;

    void ShowTip(FText& text);
    void HideTip();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* TipTextBlock;
};
