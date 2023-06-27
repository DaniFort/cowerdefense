// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

UCLASS()
class COWERDEFENSE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* playButton = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* exitButton = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FName levelToLoad;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClickPlay();

	UFUNCTION()
	void OnButtonClickExit();

};
