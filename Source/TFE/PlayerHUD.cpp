// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

APlayerHUD::APlayerHUD()
{

}

void APlayerHUD::DrawHUD()
{
    Super::DrawHUD();
}

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();

    if (ChildHealthWidgetClass)
    {
        ChildHealthWidget = CreateWidget<UChildHealthWidget>(GetWorld(), ChildHealthWidgetClass);

        if (ChildHealthWidget)
        {
            ChildHealthWidget->AddToViewport();
        }
    }
}

void APlayerHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UpdateHealthWidget();
}

void APlayerHUD::UpdateHealthWidget()
{
    if (ChildHealthWidget)
    {
        ChildHealthWidget->UpdatPercent();
    }
}
