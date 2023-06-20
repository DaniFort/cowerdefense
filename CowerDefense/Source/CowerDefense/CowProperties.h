// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(NotBlueprintType)
enum class EElements : uint8 {
	None = 0		UMETA(DisplayName = "None"),
	Fire = 1        UMETA(DisplayName = "Fire"),
	Water = 2       UMETA(DisplayName = "Water"),
	Plant = 3		UMETA(DisplayName = "Plant"),
};

class COWERDEFENSE_API CowProperties
{
public:
	CowProperties();
	~CowProperties();
};
