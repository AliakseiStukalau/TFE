#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DifficultyLevel.generated.h"


UCLASS()
class TFE_API UDifficultyLevel : public UObject
{
    GENERATED_BODY()

public:
    struct ChildHealRate
    {
        float FullPowerFireHeal;
        float MiddlePowerFireHeal;
        float LowPowerFireHeal;
        float SmokeHeal;
    };

    struct GhostStats
    {
        float GhostWalkRadius;
        float GhostPursuitRadius;
        float GhostWalkSpeed;
        float GhostPursuitSpeed;
        float ghostSightHalfAngle;
        float ghostSightRadius;
    };

    UDifficultyLevel() {};

    FString LevelName;
    int levelNumber;

    GhostStats ghostStats;
    float FireExtinctionTime;
    float TreeRespawnTime;

    float ChildInitHitPoints;
    ChildHealRate ChildHeal;
};
