// Fill out your copyright notice in the Description page of Project Settings.


#include "CowPlayerController.h"

// void ACowPlayerController::SetupInputComponent()
// {
	// if (InputComponent)
//	{
//		// Bind an action to it
//		InputComponent->BindAxisKey
//		(
//			"Horizontal", // The input identifier (specified in DefaultInput.ini)
//			this, // The object instance that is going to react to the input
//			&ACowPlayerController::Move // The function that will fire when input is received
//		); 
//	}
//}

void ACowPlayerController::Move(float horizontalMovement)
{
	UE_LOG(LogTemp, Log, TEXT("horizontal"));
}

