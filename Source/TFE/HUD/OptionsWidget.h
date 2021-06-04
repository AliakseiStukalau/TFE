#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "OptionsWidget.generated.h"

UCLASS()
class TFE_API UOptionsWidget : public UUserWidget
{
    GENERATED_BODY()
public:

    virtual void NativeConstruct() override;

    UOptionsWidget(const FObjectInitializer& objectInitializer);

    UFUNCTION()
    void OnSliderValueChanged(float newValue);

    UFUNCTION()
    void OnBackClicked();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UButton* ButtonBack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    USlider* SliderDifficulty;
};
