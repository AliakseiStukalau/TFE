// Fill out your copyright notice in the Description page of Project Settings.


#include "AFireplace.h"
#include "AWoodenTrunk.h"
#include "Kismet/GameplayStatics.h"
#include "TFECharacter.h"

// Sets default values
AAFireplace::AAFireplace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
}

// Called when the game starts or when spawned
void AAFireplace::BeginPlay()
{
	Super::BeginPlay();

	ATFECharacter *pPlayer = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (pPlayer)
	{
		pPlayer->OnDropTrunk.AddDynamic(this, &AAFireplace::OnDropTrunk);

		//UE_LOG(LogTemp, Display, TEXT("Player location:="));

		ResetFire();
	}

}

// Called every frame
void AAFireplace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAFireplace::DisableEmmiters()
{
	ParticleSystemFire->SetEmitterEnable("Smoke", false);
	ParticleSystemFire->SetEmitterEnable("Low", false);
	ParticleSystemFire->SetEmitterEnable("Middle", false);
	ParticleSystemFire->SetEmitterEnable("Full", false);

	FireState = FireIntensityState::None;
}

void AAFireplace::ResetFire()
{
	GetWorld()->GetTimerManager().ClearTimer(DecreaseFireTimerHandle);

	SetFullPower();

	GetWorld()->GetTimerManager().SetTimer(DecreaseFireTimerHandle, this, &AAFireplace::DecreaseFire, FireDecreaseTime, true);
}

void AAFireplace::SetFullPower()
{
	DisableEmmiters();

	ParticleSystemFire->SetEmitterEnable("Full", true);

	FireState = FireIntensityState::Full;
}

void AAFireplace::SetMiddlePower()
{
	DisableEmmiters();

	ParticleSystemFire->SetEmitterEnable("Middle", true);

	FireState = FireIntensityState::Middle;
}

void AAFireplace::SetLowPower()
{
	DisableEmmiters();

	ParticleSystemFire->SetEmitterEnable("Low", true);

	FireState = FireIntensityState::Low;
}

void AAFireplace::SetSmoke()
{
	DisableEmmiters();

	ParticleSystemFire->SetEmitterEnable("Smoke", true);

	FireState = FireIntensityState::Smoke;
}

void AAFireplace::DecreaseFire()
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

void AAFireplace::OnDropTrunk()
{
	ATFECharacter* pPlayer = Cast<ATFECharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (pPlayer && pPlayer->TrunkPhysicsObject->IsOverlappingActor(this))
	{
		AAWoodenTrunk* pTrunk = Cast<AAWoodenTrunk>(pPlayer->TrunkPhysicsObject->GetOwner());

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
