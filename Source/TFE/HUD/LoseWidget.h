#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LoseWidget.generated.h"

UENUM(BlueprintType)
enum class EPlayerLoseCause : uint8
{
    KilledByGhost = 0 UMETA(DisplayName = "KilledByGhost"),
    ChildHasFrozen = 1 UMETA(DisplayName = "ChildHasFrozen")
};

UCLASS()
class TFE_API ULoseWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    virtual void NativeConstruct() override;

    ULoseWidget(const FObjectInitializer& objectInitializer);

    UFUNCTION()
    void OnRestartClick();

    UFUNCTION()
    void OnQuitClick();

    UFUNCTION()
    void OnGoMenu();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UButton* ButtonRestart;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UButton* ButtonQuit;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UButton* ButtonGoMenu;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EPlayerLoseCause LoseCause;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int ResultSeconds;
};
