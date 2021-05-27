// Fill out your copyright notice in the Description page of Project Settings.


#include "Axe.h"

// Sets default values
AAxe::AAxe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("MainScene"));
	RootComponent = Scene;

	AxeMesh0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeMesh_0"));
	AxeMesh0->SetupAttachment(RootComponent);
	AxeMesh0->SetRelativeLocation(FVector(-42.0, 0.0, 0.0));
	AxeMesh0->SetComponentTickEnabled(false);
	AxeMesh0->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UMaterial> material0(TEXT("Material'/Game/Materials/Master_Material/Battle_Axe/01___Default.01___Default'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> asset0(TEXT("StaticMesh'/Game/Meshes/Decorative_Battle_Axe/axe_mesh_0.axe_mesh_0'"));
	AxeMesh0->SetStaticMesh(asset0.Object);
	AxeMesh0->SetMaterial(0, material0.Object);

	AxeMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeMesh_1"));
	AxeMesh1->SetupAttachment(RootComponent);
	AxeMesh1->SetRelativeLocation(FVector(-42.0, 0.0, 0.0));
	AxeMesh1->SetComponentTickEnabled(false);
	AxeMesh1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UMaterial> material1(TEXT("Material'/Game/Materials/Master_Material/Battle_Axe/01___Default__1.01___Default__1'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> asset1(TEXT("StaticMesh'/Game/Meshes/Decorative_Battle_Axe/axe_mesh_1.axe_mesh_1'"));
	AxeMesh1->SetStaticMesh(asset1.Object);
	AxeMesh1->SetMaterial(0, material1.Object);

	AxeMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeMesh_2"));
	AxeMesh2->SetupAttachment(RootComponent);
	AxeMesh2->SetRelativeLocation(FVector(-42.0, 0.0, 0.0));
	AxeMesh2->SetComponentTickEnabled(false);
	AxeMesh2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UMaterial> material2(TEXT("Material'/Game/Materials/Master_Material/Battle_Axe/01___Default__1.01___Default__1'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> asset2(TEXT("StaticMesh'/Game/Meshes/Decorative_Battle_Axe/axe_mesh_2.axe_mesh_2'"));
	AxeMesh2->SetStaticMesh(asset2.Object);
	AxeMesh2->SetMaterial(0, material2.Object);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->SetRelativeTransform(FTransform(FRotator(90, 0, 0).Quaternion(), FVector(8, 0, 2), FVector(0.3, 1.0, 1.0)));
}

// Called when the game starts or when spawned
void AAxe::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

