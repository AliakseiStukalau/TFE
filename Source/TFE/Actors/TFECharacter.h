// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "../HUD/Tip.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "TFECharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDropTrunkDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHideTipDelegate, TipId, tipId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowTipDelegate, UObject*, tip);


UCLASS(config=Game)
class ATFECharacter : public ACharacter
{

	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:

	ATFECharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent *TrunkPhysicsObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* GrabLocation;

	class UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GrabDistance;

	bool IsHolding;
	bool HasWeapon;
	bool IsCloseToGrabbableObject;
	bool IsFirstPersonView;


	FDropTrunkDelegate OnDropTrunk;
	FHideTipDelegate OnHideTip;
	FShowTipDelegate OnShowTip;

protected:
    
    void ReportLocation();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Grab();

	UFUNCTION(BlueprintCallable)
	void HandleReleaseObject();

	UFUNCTION(BlueprintCallable)
	bool HandleGrabObject();

	UFUNCTION(BlueprintCallable)
	void UpdateGrabbedObject();

	UFUNCTION()
	void ChangePersonView();

	UFUNCTION()
	void SetFirstPersonView();

	UFUNCTION()
	void SetThirdPersonView();

	UFUNCTION()
	void OnCharacterCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnCaracterCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};



class UMyPH : public UPhysicsHandleComponent
{

};