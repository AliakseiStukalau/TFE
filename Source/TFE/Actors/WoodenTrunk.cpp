// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodenTrunk.h"

// Sets default values
AWoodenTrunk::AWoodenTrunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TrunkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrunkMesh"));
	TrunkMesh->SetSimulatePhysics(true);
	TrunkMesh->SetMassOverrideInKg(NAME_None, 1000);
	TrunkMesh->SetLinearDamping(1);
	TrunkMesh->SetAngularDamping(2);
	TrunkMesh->SetCollisionProfileName("PhysicsActor");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Meshes/wooden_rotten_trunk.wooden_rotten_trunk'"));
	TrunkMesh->SetStaticMesh(MeshAsset.Object);
	RootComponent = TrunkMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	FTransform transform(FRotator(0.0, 0.0, 0.0), FVector(74.0, 0.0, 14.0), FVector(2.75, 1.0, 0.75));
	BoxCollision->SetRelativeTransform(transform);
}

// Called when the game starts or when spawned
void AWoodenTrunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWoodenTrunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

