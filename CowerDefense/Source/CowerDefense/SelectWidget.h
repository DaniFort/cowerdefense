// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CowPlayer.h"
#include "CowPlayerController.h"
#include "Containers/Map.h"

#include "SelectWidget.generated.h"

class UCanvasPanel;
class UButton;
class UTextBlock;
class UProgressBar;
class UWidgetAnimation;

UCLASS()
class COWERDEFENSE_API USelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* buttonsCanvasPanel = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* normalTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* normalTurretBuyPrice = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* fireTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* fireTurretBuyPrice = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* waterTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* waterTurretBuyPrice = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* plantTurretButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* plantTurretBuyPrice = nullptr;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UCanvasPanel* targetCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* targetText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* targetCowTypeText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* targetCowAttackText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* targetCowVelocityText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* targetCowRangeText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* targetNextButton = nullptr;;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* targetPreviousButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* targetCloseButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* targetSellButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* startWaveButton = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* goMenuButton = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* milkText{nullptr};
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* killsText{nullptr};	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* lifeBar{nullptr};
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* waveText {nullptr};
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* winOrLoseText {nullptr};

	int currentWave{ 0 };
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere)
	ACowPlayer* cowPlayer = nullptr;

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

	UFUNCTION()
	void OnButtonClickPrevious();
	UFUNCTION()
	void OnButtonClickNext();
	UFUNCTION()
	void OnButtonClickClose();
	UFUNCTION()
	void OnButtonClickSell();

	UFUNCTION()
	void SetMilkText(int amount);
	UFUNCTION()
	void SetKillsText(int amount);
	void UpdateLifeBar(float percent);
	UFUNCTION(BlueprintCallable)
	void SetWaveText();
	void NextWave();
	UFUNCTION()
	void StartWave();
	void WinGame();
	void OnLoseGame();
	
	//Animation
	UWidgetAnimation* nextWaveAnimation;
	UWidgetAnimation* winOrLoseAnimation;
	TMap<FName, UWidgetAnimation*>AnimationMap;

	UWidgetAnimation* GetAnimationByName(FName AnimationName)const;
	void StoreWidgetAnimations();

	UFUNCTION()
	void GOMenu();


};
