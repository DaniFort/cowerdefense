// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CowPlayer.h"
#include "CowPlayerController.h"
#include "CowProperties.h"

#include "SelectWidget.generated.h"

class UButton;

UCLASS()
class COWERDEFENSE_API USelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* normalTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* fireTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* waterTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* plantTurretButton = nullptr;

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	APawn* cowPlayer = nullptr;

	UPROPERTY(VisibleAnywhere)
	ACowPlayerController* cowPlayerPC = nullptr;
	
UFUNCTION()
	void OnButtonClickNormal();
	UFUNCTION()
	void OnButtonClickFire();
	UFUNCTION()
	void OnButtonClickWater();
	UFUNCTION()
	void OnButtonClickPlant();
};
