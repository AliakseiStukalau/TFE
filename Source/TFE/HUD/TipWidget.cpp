#include "TipWidget.h"


UTipWidget::UTipWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void UTipWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTipWidget::ShowTip(FText& text)
{
    TipTextBlock->SetText(text);
    TipTextBlock->SetVisibility(ESlateVisibility::Visible);
}

void UTipWidget::HideTip()
{
    TipTextBlock->SetVisibility(ESlateVisibility::Hidden);
}
