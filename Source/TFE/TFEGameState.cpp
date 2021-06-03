#include "TFEGameState.h"
#include "Misc/DateTime.h"

void ATFEGameState::BeginPlay()
{
    Super::BeginPlay();

    StartPlayTime = FDateTime::Now();
}
