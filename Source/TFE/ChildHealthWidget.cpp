// Fill out your copyright notice in the Description page of Project Settings.


#include "ChildHealthWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"


UChildHealthWidget::UChildHealthWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UChildHealthWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChild::StaticClass(), foundActors);
    if (foundActors.Num() > 0)
        Child = Cast<APlayerChild>(foundActors[0]);
}

void UChildHealthWidget::UpdatPercent()
{
    if (Child)
    {
        if(HealthPercentBar)
            HealthPercentBar->SetPercent(Child->HitPoints / 100);

        if (HealthPercentTxt)
        {
            if (Child->HitPointsChangePerSecond > 0)
                HealthPercentTxt->SetColorAndOpacity(FSlateColor(FLinearColor(0.0, 1.0, 0.0)));
            else if(Child->HitPointsChangePerSecond < 0)
                HealthPercentTxt->SetColorAndOpacity(FSlateColor(FLinearColor(0.0, 0.7, 1.0)));
            else
                HealthPercentTxt->SetColorAndOpacity(FSlateColor(FLinearColor(1.0, 1.0, 1.0)));

            FNumberFormattingOptions options;
            options.MaximumFractionalDigits = 0;
            //HealthPercentTxt->SetText(FText::FromString(FString::SanitizeFloat(percent.FloatValue)));
            HealthPercentTxt->SetText(FText::AsNumber(Child->HitPoints, &options));
        }
    }
}
