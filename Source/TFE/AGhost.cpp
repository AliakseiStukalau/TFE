// Fill out your copyright notice in the Description page of Project Settings.


#include "AGhost.h"

// Sets default values
AAGhost::AAGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAGhost::BeginPlay()
{
	Super::BeginPlay();

	this->GetController();
	
}

// Called every frame
void AAGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

