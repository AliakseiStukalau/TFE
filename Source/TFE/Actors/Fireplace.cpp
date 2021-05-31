#include "Fireplace.h"
#include "WoodenTrunk.h"
#include "Kismet/GameplayStatics.h"
#include "TFECharacter.h"

// Sets default values
AFireplace::AFireplace()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    FireDecreaseTime = 10; //sec

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("MainScene"));
    RootComponent = Scene;

    FireplaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireplaceMesh"));
    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Meshes/Campfire/Campfire1.Campfire1'"));
    FireplaceMesh->SetStaticMesh(MeshAsset.Object);
    FTransform fireTransform(FRotator(0.0, 0.0, 0.0), FVector(0.0, 0.0, 0.0), FVector(0.3, 0.3, 0.3));
    FireplaceMesh->SetRelativeTransform(fireTransform);
    FireplaceMesh->SetupAttachment(RootComponent);

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    FTransform boxTransform(FRotator(0.0, 0.0, 0.0), FVector(0.0, 0.0, 76.0), FVector(2.75, 2.5, 2.75));
    BoxCollision->SetRelativeTransform(boxTransform);
    BoxCollision->SetupAttachment(RootComponent);


    ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/ParticleSystems/PS_Fire.PS_Fire'"));
    ParticleSystemFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FirePS"));
    ParticleSystemFire->SetTemplate(PS.Object);
    ParticleSystemFire->SetupAttachment(RootComponent);

    PointLightOuter = CreateDefaultSubobject<UPointLightComponent>(TEXT("FirePointLightOuter"));
    PointLightOuter->SetupAttachment(RootComponent);
    PointLightOuter->LightColor = FColor(255, 194, 167);
    PointLightOuter->bUseTemperature = 1;
    PointLightOuter->Temperature = 2800;

    PointLightInner = CreateDefaultSubobject<UPointLightComponent>(TEXT("FirePointLightInner"));
    PointLightInner->SetupAttachment(RootComponent);
    PointLightInner->SetRelativeLocation(FVector(0.0, -30.0, 130.0));
    PointLightInner->LightColor = FColor(255, 194, 167);
    PointLightInner->bUseTemperature = 1;
    PointLightInner->Temperature = 1700;
    PointLightInner->CastShadows = false;
}

// Called when the game starts or when spawned
void AFireplace::BeginPlay()
{
    Super::BeginPlay();

    ATFECharacter* pPlayer = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (pPlayer)
    {
        pPlayer->OnDropTrunk.AddDynamic(this, &AFireplace::OnDropTrunk);
        ResetFire();
        OnFireChange.Broadcast();
    }

}

// Called every frame
void AFireplace::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AFireplace::DisableEmmiters()
{
    ParticleSystemFire->SetEmitterEnable("Smoke", false);
    ParticleSystemFire->SetEmitterEnable("Low", false);
    ParticleSystemFire->SetEmitterEnable("Middle", false);
    ParticleSystemFire->SetEmitterEnable("Full", false);

    FireState = FireIntensityState::None;
}

void AFireplace::ResetFire()
{
    GetWorld()->GetTimerManager().ClearTimer(DecreaseFireTimerHandle);

    SetFullPower();

    GetWorld()->GetTimerManager().SetTimer(DecreaseFireTimerHandle, this, &AFireplace::DecreaseFire, FireDecreaseTime, true);
}

void AFireplace::SetFullPower()
{
    DisableEmmiters();

    ParticleSystemFire->SetEmitterEnable("Full", true);
    
    PointLightOuter->SetRelativeLocation(FVector(0.0, -30.0, 300.0));
    PointLightOuter->SetIntensity(8500);
    PointLightOuter->SetAttenuationRadius(600);

    PointLightInner->SetIntensity(3000);
    PointLightInner->SetAttenuationRadius(270);

    FireState = FireIntensityState::Full;
}

void AFireplace::SetMiddlePower()
{
    DisableEmmiters();

    ParticleSystemFire->SetEmitterEnable("Middle", true);
    
    PointLightOuter->SetRelativeLocation(FVector(0.0, -30.0, 230.0));
    PointLightOuter->SetIntensity(5500);
    PointLightOuter->SetAttenuationRadius(420);

    PointLightInner->SetIntensity(2000);
    PointLightInner->SetAttenuationRadius(200);

    FireState = FireIntensityState::Middle;
}

void AFireplace::SetLowPower()
{
    DisableEmmiters();

    ParticleSystemFire->SetEmitterEnable("Low", true);
    
    PointLightOuter->SetRelativeLocation(FVector(0.0, -30.0, 135.0));
    PointLightOuter->SetIntensity(1500);
    PointLightOuter->SetAttenuationRadius(300);

    PointLightInner->SetIntensity(1500);
    PointLightInner->SetAttenuationRadius(200);

    FireState = FireIntensityState::Low;
}

void AFireplace::SetSmoke()
{
    DisableEmmiters();

    ParticleSystemFire->SetEmitterEnable("Smoke", true);

    PointLightOuter->SetIntensity(0);

    PointLightInner->SetIntensity(300);
    PointLightInner->SetAttenuationRadius(200);

    FireState = FireIntensityState::Smoke;
}

void AFireplace::DecreaseFire()
{
    switch (FireState)
    {
    case FireIntensityState::Middle:
        SetLowPower();
        break;
    case FireIntensityState::Full:
        SetMiddlePower();
        break;
    case FireIntensityState::None:
    case FireIntensityState::Smoke:
    case FireIntensityState::Low:
    default:
        SetSmoke();
        break;
    }

    OnFireChange.Broadcast();
}

void AFireplace::OnDropTrunk()
{
    ATFECharacter* pPlayer = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (pPlayer && pPlayer->TrunkPhysicsObject->IsOverlappingActor(this))
    {
        AWoodenTrunk* pTrunk = Cast<AWoodenTrunk>(pPlayer->TrunkPhysicsObject->GetOwner());

        if (pTrunk)
        {
            ResetFire();
            OnFireChange.Broadcast();

            FTimerHandle    handle;
            GetWorld()->GetTimerManager().SetTimer(handle, [pTrunk]() {
                pTrunk->Destroy();
                }, 2, false);

        }
    }
}
