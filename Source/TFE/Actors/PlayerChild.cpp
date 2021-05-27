// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChild.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerChild::APlayerChild()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/Meshes/1M_Cube.1M_Cube'"));
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
		case FireIntensityState::Full:
			HitPointsChangePerSecond = 3;
			break;
		case FireIntensityState::Middle:
			HitPointsChangePerSecond = 1;
			break;
		case FireIntensityState::Low:
			HitPointsChangePerSecond = 0;
			break;
		case FireIntensityState::Smoke:
		case FireIntensityState::None:
		default:
			HitPointsChangePerSecond = -2;
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
		//You loose
	}
}

