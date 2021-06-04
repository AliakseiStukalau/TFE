#pragma once

#include "CoreMinimal.h"
#include "../Actors/PlayerChild.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "ChildHealthWidget.generated.h"


UCLASS()
class TFE_API UChildHealthWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UChildHealthWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    UFUNCTION()
    void UpdatePercent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* HealthPercentTxt;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    class UProgressBar* HealthPercentBar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    APlayerChild* Child;
};
