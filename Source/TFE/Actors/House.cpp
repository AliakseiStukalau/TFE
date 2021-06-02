#include "House.h"

// Sets default values
AHouse::AHouse()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    MainScene = CreateDefaultSubobject<USceneComponent>(TEXT("MainScene"));
    MainScene->SetWorldScale3D(FVector(1.3, 1.3, 1.3));
    RootComponent = MainScene;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetRelativeScale3D(FVector(6.0, 6.0, 4.5));
    TriggerBox->SetRelativeLocation(FVector(200.0, -194.0, 150.0));
    TriggerBox->SetupAttachment(RootComponent);

    const ConstructorHelpers::FObjectFinder<UStaticMesh> objWallDoorOpposite(TEXT("StaticMesh'/Game/Meshes/House/Wall_400x300.Wall_400x300'"));
    const ConstructorHelpers::FObjectFinder<UStaticMesh> objWallWindowOpposite(TEXT("StaticMesh'/Game/Meshes/House/Wall_400x300.Wall_400x300'"));
    const ConstructorHelpers::FObjectFinder<UStaticMesh> objWallWindow(TEXT("StaticMesh'/Game/Meshes/House/Wall_Window_400x300.Wall_Window_400x300'"));
    const ConstructorHelpers::FObjectFinder<UStaticMesh> objWallDoor(TEXT("StaticMesh'/Game/Meshes/House/Wall_Door_400x300.Wall_Door_400x300'"));
    const ConstructorHelpers::FObjectFinder<UStaticMesh> objRoof(TEXT("StaticMesh'/Game/Meshes/House/Wall_400x400.Wall_400x400'"));

    MeshWallDoorOpposite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshWallDoorOpposite"));
    MeshWallDoorOpposite->SetStaticMesh(objWallDoorOpposite.Object);
    MeshWallDoorOpposite->SetRelativeLocation(FVector(0.0, -380.0, 0.0));
    MeshWallDoorOpposite->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
    MeshWallDoorOpposite->SetupAttachment(RootComponent);

    MeshWallWindowOpposite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshWallWindowOpposite"));
    MeshWallWindowOpposite->SetStaticMesh(objWallWindowOpposite.Object);
    MeshWallWindowOpposite->SetRelativeLocation(FVector(-10.0, 10.0, 0.0));
    MeshWallWindowOpposite->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
    MeshWallWindowOpposite->SetupAttachment(RootComponent);

    MeshWallWindow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshWallWindow"));
    MeshWallWindow->SetStaticMesh(objWallWindow.Object);
    MeshWallWindow->SetRelativeLocation(FVector(410.0, 10.0, 300.0));
    MeshWallWindow->SetRelativeRotation(FRotator(0.0, -90.0, -180.0));
    MeshWallWindow->SetupAttachment(RootComponent);

    MeshWallDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshWallDoor"));
    MeshWallDoor->SetStaticMesh(objWallDoor.Object);
    MeshWallDoor->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
    MeshWallDoor->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
    MeshWallDoor->SetupAttachment(RootComponent);

    MeshRoof = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshRoof"));
    MeshRoof->SetStaticMesh(objRoof.Object);
    MeshRoof->SetRelativeLocation(FVector(-20.0, -390.0, 310.0));
    MeshRoof->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
    MeshRoof->SetupAttachment(RootComponent);
    MeshRoof->SetRelativeScale3D(FVector(1.1, 1.0, 1.0));
}

