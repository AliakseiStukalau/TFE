#include "OptionsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../TFEGameMode.h"
#include "TFE/DifficultyLevel.h"
#include "TFE/TFEGameInstance.h"

void UOptionsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (SliderDifficulty)
    {
        UTFEGameInstance* gameInstance = Cast<UTFEGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
        if (gameInstance)
        {
            UDifficultyLevel* difficulty = gameInstance->GetCurrentDifficulty();
            SliderDifficulty->SetValue(difficulty->levelNumber);

        }

        SliderDifficulty->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnSliderValueChanged);
    }

    if (ButtonBack)
    {
        ButtonBack->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackClicked);
    }
}

UOptionsWidget::UOptionsWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UOptionsWidget::OnSliderValueChanged(float newValue)
{
    UTFEGameInstance* gameInstance = Cast<UTFEGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (gameInstance)
    {
        UDifficultyLevel* dLevel = gameInstance->GetCurrentDifficulty();
        gameInstance->UpdateDifficulty(static_cast<int>(newValue));
    }
}

void UOptionsWidget::OnBackClicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Menu");
}
