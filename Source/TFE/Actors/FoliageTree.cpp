#include "FoliageTree.h"
#include "TFECharacter.h"
#include "WoodenTrunk.h"

// Sets default values
AFoliageTree::AFoliageTree()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    RespawnTime = 600; //sec

    TreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh_"));
    RootComponent = TreeMesh;

    TreeMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void AFoliageTree::BeginPlay()
{
    Super::BeginPlay();
    TreeMesh->OnComponentHit.AddDynamic(this, &AFoliageTree::OnCompHit);
}

void AFoliageTree::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    ATFECharacter* pPlayer = Cast<ATFECharacter>(OtherActor);
    if (pPlayer)
    {
        if (pPlayer->HasWeapon)
        {
            UE_LOG(LogTemp, Display, TEXT("Player location"));
            TreeMesh->SetVisibility(false, true);
            TreeMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

            FActorSpawnParameters spawnInfo;
            spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;

            FVector location(GetActorLocation());
            const FRotator rotation1(0.0f, 0.0f, 90.0f);
            location.Z += 100;
            const FRotator rotation2(90.0f, 0.0f, 0.0f);

            AWoodenTrunk* trunk1 = GetWorld()->SpawnActor<AWoodenTrunk>(location, rotation1, spawnInfo);
            if (trunk1->GetRootComponent())
                trunk1->GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);

            AWoodenTrunk* trunk2 = GetWorld()->SpawnActor<AWoodenTrunk>(location, rotation2, spawnInfo);
            if (trunk2->GetRootComponent())
                trunk2->GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);


            FTimerHandle    handle;
            GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
                TreeMesh->SetVisibility(true, true);
                TreeMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
                }, RespawnTime, false);
        }
    }
}

