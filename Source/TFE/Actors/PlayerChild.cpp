#include "PlayerChild.h"
#include "TFECharacter.h"
#include "../HUD/LoseWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerChild::APlayerChild()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    ChildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildMesh"));
    const ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/Meshes/SittingChildMesh.SittingChildMesh'"));
    ChildMesh->SetStaticMesh(meshAsset.Object);
    RootComponent = ChildMesh;
    HitPoints = 50;
    Fireplace = nullptr;
}

// Called when the game starts or when spawned
void APlayerChild::BeginPlay()
{
    Super::BeginPlay();

    InitFireplace();

    if (Fireplace)
        Fireplace->OnFireChange.AddDynamic(this, &APlayerChild::CalcHitPointsDelta);

    CalcHitPointsDelta();
}

void APlayerChild::InitFireplace()
{
    if (Fireplace == nullptr)
    {
        TArray<AActor*> foundActors;
        TSubclassOf<AFireplace> actorToFind = AFireplace::StaticClass();
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), actorToFind, foundActors);
        if (foundActors.Num() > 0)
            Fireplace = Cast<AFireplace>(foundActors[0]);
    }
}

void APlayerChild::CalcHitPointsDelta()
{
    if (Fireplace)
    {
        switch (Fireplace->FireState)
        {
        case EFireIntensityState::Full:
            HitPointsChangePerSecond = 2;
            break;
        case EFireIntensityState::Middle:
            HitPointsChangePerSecond = 1;
            break;
        case EFireIntensityState::Low:
            HitPointsChangePerSecond = -1;
            break;
        case EFireIntensityState::Smoke:
        case EFireIntensityState::None:
        default:
            HitPointsChangePerSecond = -4;
            break;
        }
    }
}

// Called every frame
void APlayerChild::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HitPoints += HitPointsChangePerSecond * DeltaTime;

    if (HitPoints > 100)
        HitPoints = 100;

    if (HitPoints <= 0)
    {
        HitPoints = 0;
        ATFECharacter* pPlayer = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

        if (pPlayer)
        {
            pPlayer->OnPlayerLose.Broadcast(EPlayerLoseCause::ChildHasFrozen);
        }
    }
}

