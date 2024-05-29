// Copyright Epic Games, Inc. All Rights Reserved.

#include "NukeRPGGameMode.h"
#include "NukeRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANukeRPGGameMode::ANukeRPGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
