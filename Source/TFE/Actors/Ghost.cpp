#include "Ghost.h"

#include "AIController.h"
#include "TFECharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFE/DifficultyLevel.h"
#include "TFE/TFEGameInstance.h"

// Sets default values
AGhost::AGhost()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    IsPlayerDetected = false;

    const ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/ParticleSystems/PS_GhostSmoke.PS_GhostSmoke'"));
    SmokePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokePS"));
    SmokePS->SetupAttachment(GetMesh());
    SmokePS->SetRelativeLocation(FVector(0.0, 0.0, -20.0));
    SmokePS->SetTemplate(PS.Object);

    const ConstructorHelpers::FObjectFinder<UStaticMesh> headMesh(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
    const ConstructorHelpers::FObjectFinder<UMaterialInstance> headMI(TEXT("MaterialInstance'/Game/Materials/Child_Material/MI_GhostHead.MI_GhostHead'"));
    GhostHeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostHeadMesh"));
    GhostHeadMesh->SetupAttachment(GetMesh());
    GhostHeadMesh->SetRelativeLocation(FVector(35.0, 0.0, 37.0));
    GhostHeadMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
    GhostHeadMesh->SetRelativeRotation(FRotator(-50.0, 0.0, 0.0));
    GhostHeadMesh->SetStaticMesh(headMesh.Object);
    GhostHeadMesh->SetMaterial(0, headMI.Object);

    AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
    AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
    AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
    AIPerception->ConfigureSense(*AISightConfig);
    AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AGhost::OnTargetPerceptionUpd);
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
    Super::BeginPlay();

    UTFEGameInstance* gameInstance = Cast<UTFEGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (gameInstance)
    {
        UDifficultyLevel* dLevel = gameInstance->GetCurrentDifficulty();
        AttackMovementSpeed = dLevel->ghostStats.GhostPursuitSpeed;
        UsualMovementSpeed = dLevel->ghostStats.GhostWalkSpeed;
        PursuitRadius = dLevel->ghostStats.GhostPursuitRadius;
        WalkRadius = dLevel->ghostStats.GhostWalkRadius;

        AISightConfig->SightRadius = dLevel->ghostStats.ghostSightRadius;
        AISightConfig->LoseSightRadius = 1.2 * AISightConfig->SightRadius;
        AISightConfig->PeripheralVisionAngleDegrees = dLevel->ghostStats.ghostSightHalfAngle;
    }
    else
    {
        AttackMovementSpeed = 650.0;
        UsualMovementSpeed = 400.0;
        PursuitRadius = 4000.0;
        WalkRadius = 3000.0;

        AISightConfig->SightRadius = 1000;
        AISightConfig->LoseSightRadius = 1.2 * AISightConfig->SightRadius;
        AISightConfig->PeripheralVisionAngleDegrees = 70;
    }


    AAIController* aic = Cast<AAIController>(this->GetController());
    Blackboard = (aic->GetBlackboardComponent());

    if (Blackboard)
    {
        InitialLocation = this->GetActorLocation();
        Blackboard->SetValueAsVector("InitialLocation", this->GetActorLocation());
        Blackboard->ClearValue("IsTooFarFromInitialLocation");
    }
}

void AGhost::OnTargetPerceptionUpd(AActor* Actor, FAIStimulus Stimulus)
{
    if (Cast<ATFECharacter>(Actor))
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, "Here you are!!");

            GetCharacterMovement()->MaxWalkSpeed = AttackMovementSpeed;

            Blackboard->SetValueAsBool("CanSeePlayer", true);
        }
        else
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, "(((((");

            GetCharacterMovement()->MaxWalkSpeed = UsualMovementSpeed;

            Blackboard->ClearValue("CanSeePlayer");
        }
    }
}

