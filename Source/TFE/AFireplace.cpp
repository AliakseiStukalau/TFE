// Fill out your copyright notice in the Description page of Project Settings.


#include "AFireplace.h"
#include "Kismet/GameplayStatics.h"
#include "TFECharacter.h"

// Sets default values
AAFireplace::AAFireplace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("MainScene"));
	RootComponent = Scene;

	FireplaceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireplaceMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Meshes/Campfire/Campfire1.Campfire1'"));
	FireplaceMesh->SetStaticMesh(MeshAsset.Object);
	FTransform fireTransform(FRotator(0.0, 0.0, 0.0), FVector(0.0, 0.0, 0.0), FVector(0.3, 0.3, 0.3));
	FireplaceMesh->SetRelativeTransform(fireTransform);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	FTransform boxTransform(FRotator(0.0, 0.0, 0.0), FVector(0.0, 0.0, 76.0), FVector(2.75, 2.5, 2.75));
	BoxCollision->SetRelativeTransform(boxTransform);


	ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/ParticleSystems/PS_Fire.PS_Fire'"));
	ParticleSystemFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FirePS"));
	ParticleSystemFire->SetTemplate(PS.Object);
}

// Called when the game starts or when spawned
void AAFireplace::BeginPlay()
{
	Super::BeginPlay();

	ATFECharacter *player = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (player)
	{
		UE_LOG(LogTemp, Display, TEXT("Player location:="));
	}

}

// Called every frame
void AAFireplace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

