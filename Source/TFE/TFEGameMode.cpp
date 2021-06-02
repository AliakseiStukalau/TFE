#include "TFEGameMode.h"
#include "Actors/TFECharacter.h"
#include "UObject/ConstructorHelpers.h"

ATFEGameMode::ATFEGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
