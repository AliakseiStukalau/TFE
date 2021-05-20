// Fill out your copyright notice in the Description page of Project Settings.


#include "AFoliageTree.h"
#include "TFECharacter.h"
#include "AWoodenTrunk.h"

// Sets default values
AAFoliageTree::AAFoliageTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RespawnTime = 120; //sec


	TreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh_"));
}

// Called when the game starts or when spawned
void AAFoliageTree::BeginPlay()
{
	Super::BeginPlay();
	TreeMesh->OnComponentHit.AddDynamic(this, &AAFoliageTree::OnCompHit);
}

void AAFoliageTree::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ATFECharacter *pPlayer = Cast<ATFECharacter>(OtherActor);
	if (pPlayer)
	{
		//if(false)
		if (pPlayer->HasWeapon)
		{
			UE_LOG(LogTemp, Display, TEXT("Player location"));
			TreeMesh->SetVisibility(false, true);
			TreeMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

			FActorSpawnParameters spawnInfo;
			spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;

			FVector location(GetActorLocation());
			FRotator rotation1(0.0f, 0.0f, 90.0f);

			AAWoodenTrunk *trunk1 = GetWorld()->SpawnActor<AAWoodenTrunk>(location, rotation1, spawnInfo);


			location.Z += 100;
			FRotator rotation2(90.0f, 0.0f, 0.0f);
			AAWoodenTrunk* trunk2 = GetWorld()->SpawnActor<AAWoodenTrunk>(location, rotation2, spawnInfo);

			if(trunk1->GetRootComponent())
				trunk1->GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);

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

// Called every frame
void AAFoliageTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

