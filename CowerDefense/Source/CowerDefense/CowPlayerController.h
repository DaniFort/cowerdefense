// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CowPlayerController.generated.h"



UCLASS()
class COWERDEFENSE_API ACowPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(float horizontalMovement);
};
