// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

APlayerHUD::APlayerHUD()
{
    CurrentTipId = TipId::None;
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

    if (TipWidgetClass)
    {
        TipWidget = CreateWidget<UTipWidget>(GetWorld(), TipWidgetClass);

        if (TipWidget)
        {
            TipWidget->AddToViewport();
        }
    }

    if (StaticTipsWidgetClass)
    {
        StaticTipsWidget = CreateWidget<UStaticTipsWidget>(GetWorld(), StaticTipsWidgetClass);

        if (StaticTipsWidget)
        {
            StaticTipsWidget->AddToViewport();
        }
    }

    ATFECharacter* pPlayer = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (pPlayer)
    {
        pPlayer->OnShowTip.AddDynamic(this, &APlayerHUD::ShowTipWidget);
        pPlayer->OnHideTip.AddDynamic(this, &APlayerHUD::HideTipWidget);
        pPlayer->OnPlayerLose.AddDynamic(this, &APlayerHUD::ShowYouLoseWidget);
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

void APlayerHUD::ShowTipWidget(UObject* pTip)
{
    UTip* tipObj = dynamic_cast<UTip*>(pTip);
    CurrentTipId = tipObj->GetId();

    if (TipWidget)
    {
        FText text = tipObj->GetText();
        TipWidget->ShowTip(text);
    }
}

void APlayerHUD::HideTipWidget(TipId tipId)
{
    if (TipWidget && tipId == CurrentTipId)
    {
        TipWidget->HideTip();
        CurrentTipId = TipId::None;
    }
}

void APlayerHUD::ShowYouLoseWidget(EPlayerLoseCause loseCause)
{
    if (YouLoseWidgetClass)
    {
        YouLoseWidget = CreateWidget<ULoseWidget>(GetWorld(), YouLoseWidgetClass);
        YouLoseWidget->LoseCause = loseCause;

        if (YouLoseWidget)
        {
            YouLoseWidget->AddToViewport();
        }
    }
}
