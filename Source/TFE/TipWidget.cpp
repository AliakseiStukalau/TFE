// Fill out your copyright notice in the Description page of Project Settings.


#include "TipWidget.h"


UTipWidget::UTipWidget(const FObjectInitializer& objectInitialiser) : Super(objectInitialiser)
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
