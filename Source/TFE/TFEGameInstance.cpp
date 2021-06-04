#include "TFEGameInstance.h"

UDifficultyLevel* UTFEGameInstance::GetDifficultyLevel0() const
{
    UDifficultyLevel::ChildHealRate childHeal;
    childHeal.FullPowerFireHeal = 3;
    childHeal.MiddlePowerFireHeal = 1;
    childHeal.LowPowerFireHeal = 0;
    childHeal.SmokeHeal = -2;

    UDifficultyLevel* difficulty = NewObject<UDifficultyLevel>();
    difficulty->ChildHeal = childHeal;
    difficulty->ChildInitHitPoints = 80;

    difficulty->FireExtinctionTime = 9;
    difficulty->TreeRespawnTime = 450;

    difficulty->ghostStats.GhostPursuitSpeed = 650;
    difficulty->ghostStats.GhostWalkSpeed = 400;
    difficulty->ghostStats.GhostPursuitRadius = 3500;
    difficulty->ghostStats.GhostWalkRadius = 3000;
    difficulty->ghostStats.ghostSightRadius = 1000;
    difficulty->ghostStats.ghostSightHalfAngle = 70;

    difficulty->LevelName = FString("Easy");
    difficulty->levelNumber = 0;

    return difficulty;
}

UDifficultyLevel* UTFEGameInstance::GetDifficultyLevel1() const
{
    UDifficultyLevel::ChildHealRate childHeal;
    childHeal.FullPowerFireHeal = 2;
    childHeal.MiddlePowerFireHeal = 1;
    childHeal.LowPowerFireHeal = -1;
    childHeal.SmokeHeal = -4;

    UDifficultyLevel* difficulty = NewObject<UDifficultyLevel>();
    difficulty->ChildHeal = childHeal;
    difficulty->ChildInitHitPoints = 50;

    difficulty->FireExtinctionTime = 7;
    difficulty->TreeRespawnTime = 600;

    difficulty->ghostStats.GhostPursuitSpeed = 650;
    difficulty->ghostStats.GhostWalkSpeed = 400;
    difficulty->ghostStats.GhostPursuitRadius = 4000;
    difficulty->ghostStats.GhostWalkRadius = 3000;
    difficulty->ghostStats.ghostSightRadius = 1000;
    difficulty->ghostStats.ghostSightHalfAngle = 70;

    difficulty->LevelName = FString("Normal");
    difficulty->levelNumber = 1;

    return difficulty;
}

UDifficultyLevel* UTFEGameInstance::GetDifficultyLevel2() const
{
    UDifficultyLevel::ChildHealRate childHeal;
    childHeal.FullPowerFireHeal = 2;
    childHeal.MiddlePowerFireHeal = 1;
    childHeal.LowPowerFireHeal = -1;
    childHeal.SmokeHeal = -5;

    UDifficultyLevel* difficulty = NewObject<UDifficultyLevel>();
    difficulty->ChildHeal = childHeal;
    difficulty->ChildInitHitPoints = 30;

    difficulty->FireExtinctionTime = 7;
    difficulty->TreeRespawnTime = 1200;

    difficulty->ghostStats.GhostPursuitSpeed = 750;
    difficulty->ghostStats.GhostWalkSpeed = 500;
    difficulty->ghostStats.GhostPursuitRadius = 4500;
    difficulty->ghostStats.GhostWalkRadius = 3000;
    difficulty->ghostStats.ghostSightRadius = 1500;
    difficulty->ghostStats.ghostSightHalfAngle = 90;

    difficulty->LevelName = FString("Hard");
    difficulty->levelNumber = 2;

    return difficulty;
}


UTFEGameInstance::UTFEGameInstance()
{
    DifficultyLevels.Add(GetDifficultyLevel0());
    DifficultyLevels.Add(GetDifficultyLevel1());
    DifficultyLevels.Add(GetDifficultyLevel2());

    CurrentDifficultyLevel = DifficultyLevels[1];
}

void UTFEGameInstance::UpdateDifficulty(int newValue)
{
    if (DifficultyLevels.IsValidIndex(newValue))
    {
        CurrentDifficultyLevel = DifficultyLevels[newValue];
        UE_LOG(LogTemp, Display, TEXT("New difficulty level: %d"), newValue);
    }
}

UDifficultyLevel* UTFEGameInstance::GetCurrentDifficulty()
{
    return CurrentDifficultyLevel;
}
