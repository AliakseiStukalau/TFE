#include "LoseWidget.h"
#include "../TFEGameState.h"
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
    ButtonGoMenu->OnClicked.AddDynamic(this, &ULoseWidget::OnGoMenu);

    ATFEGameState* gameState = Cast<ATFEGameState>(GetWorld()->GetGameState());
    if(gameState)
    {
        ResultSeconds = static_cast<int>((FDateTime::Now() - gameState->StartPlayTime).GetTotalSeconds());
    }
}

ULoseWidget::ULoseWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
}

void ULoseWidget::OnRestartClick()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
}

void ULoseWidget::OnQuitClick()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULoseWidget::OnGoMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), "Menu");
}

