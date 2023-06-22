// Fill out your copyright notice in the Description page of Project Settings.

#include "CowPlayerController.h"
#include "CowPlayer.h"


void ACowPlayerController::SetPlayerBool(bool bIsPlacingTurret, EElements elementType)
{
	cowPlayer = Cast<ACowPlayer>(GetPawn());
	cowPlayer->SetIsPlacingTurret(bIsPlacingTurret, elementType);
}

