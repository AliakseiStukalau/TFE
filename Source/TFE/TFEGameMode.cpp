// Copyright Epic Games, Inc. All Rights Reserved.

#include "TFEGameMode.h"
#include "TFECharacter.h"
#include "UObject/ConstructorHelpers.h"

ATFEGameMode::ATFEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
