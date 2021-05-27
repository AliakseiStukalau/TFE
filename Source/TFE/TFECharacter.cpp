// Copyright Epic Games, Inc. All Rights Reserved.

#include "TFECharacter.h"
#include "AFireplace.h"
#include "AWoodenTrunk.h"
#include "Axe.h"
#include "HUD/GetAxeTip.h"
#include "HUD/GrabTip.h"
#include "Engine/World.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "DrawDebugHelpers.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ATFECharacter

ATFECharacter::ATFECharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	GrabDistance = 450;
	IsCloseToGrabbableObject = false;
	IsHolding = false;
	HasWeapon = false;
	IsFirstPersonView = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PlayerPhysicsHandle"));

	GrabLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GrabLocation"));
	GrabLocation->SetupAttachment(RootComponent);
	GrabLocation->SetRelativeLocation(FVector(150.0, 0.0, 60.0));
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeScale3D(FVector(2.75, 1.75, 3.0));
	BoxCollision->SetRelativeLocation(FVector(50.0, 0.0, -10.0));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATFECharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATFECharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATFECharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATFECharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATFECharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATFECharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATFECharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATFECharacter::OnResetVR);
    
	PlayerInputComponent->BindAction("ReportLocation", EInputEvent::IE_Pressed, this, &ATFECharacter::ReportLocation);
	PlayerInputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &ATFECharacter::Grab);
	PlayerInputComponent->BindAction("ChangeView", EInputEvent::IE_Pressed, this, &ATFECharacter::ChangePersonView);
}

void ATFECharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGrabbedObject();
}

void ATFECharacter::BeginPlay()
{
	Super::BeginPlay();

	OnShowTip.Broadcast(NewObject<UGetAxeTip>());

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATFECharacter::OnCharacterCapsuleBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ATFECharacter::OnCaracterCapsuleHit);

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATFECharacter::OnBoxCollisionBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATFECharacter::OnBoxCollisionEndOverlap);
	}
}

void ATFECharacter::ReportLocation()
{
    FVector location = GetActorLocation();
    
    UE_LOG(LogTemp, Display, TEXT("Player location: %s"), *(location.ToString()));
}

void ATFECharacter::OnResetVR()
{
	// If TFE is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in TFE.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATFECharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATFECharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATFECharacter::Grab()
{
	if (IsHolding)
	{
		HandleReleaseObject();
		IsHolding = false;
	}
	else
	{
		if (HandleGrabObject())
		{
			IsHolding = true;
			OnHideTip.Broadcast(NewObject<UGrabTip>()->GetId());
		}
	}

}

void ATFECharacter::HandleReleaseObject()
{
	if (Cast<AAWoodenTrunk>(TrunkPhysicsObject->GetOwner()))
	{
		OnDropTrunk.Broadcast();

		PhysicsHandle->ReleaseComponent();

		TrunkPhysicsObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		TrunkPhysicsObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	}
}

bool ATFECharacter::HandleGrabObject()
{
	bool isSuccessTraceAndGrab = false;

	if (IsCloseToGrabbableObject)
	{
		FHitResult hitResult;
		FVector startLocation = FollowCamera->GetComponentLocation();
		FVector endLocation = startLocation + (GrabDistance * FollowCamera->GetForwardVector());

		const FName traceTag("MyTraceTag");
		GetWorld()->DebugDrawTraceTag = traceTag;

		FCollisionQueryParams queryParams;
		queryParams.bDebugQuery = true;
		queryParams.AddIgnoredActor(this);
		queryParams.TraceTag = traceTag;
		
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, 3, 0, 1.0f);

		if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Camera, queryParams))
		{
			if (PhysicsHandle && Cast<AAWoodenTrunk>(hitResult.Actor.Get()))
			{
				TrunkPhysicsObject = hitResult.Component.Get();

				PhysicsHandle->GrabComponentAtLocation(TrunkPhysicsObject, "None", hitResult.Location);

				TrunkPhysicsObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
				TrunkPhysicsObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

				isSuccessTraceAndGrab = true;
			}
		}
	}

	return isSuccessTraceAndGrab;
}

void ATFECharacter::UpdateGrabbedObject()
{
	if (IsHolding && PhysicsHandle)
	{
		PhysicsHandle->SetTargetLocationAndRotation(GrabLocation->GetComponentLocation(), GetControlRotation());
	}
}

void ATFECharacter::ChangePersonView()
{
	if (IsFirstPersonView)
	{
		SetThirdPersonView();
		IsFirstPersonView = false;

		GrabDistance += GetCameraBoom()->TargetArmLength;
	}
	else
	{
		SetFirstPersonView();
		IsFirstPersonView = true;

		GrabDistance -= GetCameraBoom()->TargetArmLength;
	}
}

void ATFECharacter::SetFirstPersonView()
{
	FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	GetFollowCamera()->AttachToComponent(GetMesh(), rules, "head");
	GetFollowCamera()->AddLocalOffset(FVector(-10.0, 26.0, 0.0), false, nullptr, ETeleportType::TeleportPhysics);
	GetFollowCamera()->AddLocalRotation(FRotator(-90.0, 0.0, 0.0).Quaternion(), false, nullptr, ETeleportType::TeleportPhysics);
	GetFollowCamera()->AddLocalRotation(FRotator(0.0, 90.0, 0.0).Quaternion(), false, nullptr, ETeleportType::TeleportPhysics);

	bUseControllerRotationYaw = true;
}

void ATFECharacter::SetThirdPersonView()
{
	bUseControllerRotationYaw = false;

	FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	GetFollowCamera()->AttachToComponent(GetCameraBoom(), rules, "head");

	FRotator deltaRotation(GetCapsuleComponent()->GetRelativeRotation().Pitch * (-1), 0, 0);
	GetCapsuleComponent()->AddLocalRotation(deltaRotation.Quaternion(), false, nullptr, ETeleportType::TeleportPhysics);

	GetFollowCamera()->AddLocalRotation(FRotator(90.0, -90.0, 0).Quaternion(), false, nullptr, ETeleportType::TeleportPhysics);

	FVector deltaLocation = GetFollowCamera()->GetRelativeLocation() * (-1);
	GetFollowCamera()->AddLocalOffset(deltaLocation, false, nullptr, ETeleportType::TeleportPhysics);
}

void ATFECharacter::OnCharacterCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAxe* pAxe = Cast<AAxe>(OtherActor);

	if (pAxe)
	{
		FAttachmentTransformRules attachmentRules(EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
		pAxe->AttachToComponent(GetMesh(), attachmentRules, FName("weapon_r"));

		HasWeapon = true;

		OnHideTip.Broadcast(NewObject<UGetAxeTip>()->GetId());
	}
}

void ATFECharacter::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAWoodenTrunk* pTrunk = Cast<AAWoodenTrunk>(OtherActor);

	if (pTrunk)
	{
		if (pTrunk->GetRootComponent()->IsSimulatingPhysics())
		{
			OnShowTip.Broadcast(NewObject<UGrabTip>());
			IsCloseToGrabbableObject = true;
		}
	}
	else
	{
		OnHideTip.Broadcast(NewObject<UGrabTip>()->GetId());
	}
}

void ATFECharacter::OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAWoodenTrunk* pTrunk = Cast<AAWoodenTrunk>(OtherActor);

	if (pTrunk)
	{
		OnHideTip.Broadcast(NewObject<UGrabTip>()->GetId());
		IsCloseToGrabbableObject = false;
	}
}

void ATFECharacter::OnCaracterCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString actorName = UKismetSystemLibrary::GetDisplayName(OtherActor);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, actorName);

}

void ATFECharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATFECharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATFECharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATFECharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
