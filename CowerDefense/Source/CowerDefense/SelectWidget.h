// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CowPlayer.h"
#include "CowPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SelectWidget.generated.h"

class UButton;

UCLASS()
class COWERDEFENSE_API USelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* normalTurretButton = nullptr;

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	APawn* cowPlayer = nullptr;

	UPROPERTY(VisibleAnywhere)
	ACowPlayerController* cowPlayerPC = nullptr;
	
UFUNCTION()
	void OnButtonClickNormal();
};
