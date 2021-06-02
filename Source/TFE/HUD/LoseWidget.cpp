// Fill out your copyright notice in the Description page of Project Settings.


#include "LoseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ULoseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UGameplayStatics::SetGamePaused(GetWorld(), true);

    APlayerController *pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if(pPlayerController)
    {
        pPlayerController->SetShowMouseCursor(true);
        
        FInputModeUIOnly inputMode;
        inputMode.SetWidgetToFocus(TakeWidget());
        pPlayerController->SetInputMode(FInputModeUIOnly());
    }

    ButtonRestart->OnClicked.AddDynamic(this, &ULoseWidget::OnRestartClick);
    ButtonQuit->OnClicked.AddDynamic(this, &ULoseWidget::OnQuitClick);
}

ULoseWidget::ULoseWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void ULoseWidget::OnRestartClick()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void ULoseWidget::OnQuitClick()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
