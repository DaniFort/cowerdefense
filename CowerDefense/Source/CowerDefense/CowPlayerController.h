// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "CowPlayer.h"
#include "CowProperties.h"
#include "GameFramework/PlayerController.h"
#include "CowPlayerController.generated.h"

class ACowPlayer;

UCLASS()
class COWERDEFENSE_API ACowPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void SetPlayerBool(bool bIsPlacingTurret, EElements elementType);

	UPROPERTY(VisibleDefaultsOnly)
	ACowPlayer* cowPlayer = nullptr;

	
};
