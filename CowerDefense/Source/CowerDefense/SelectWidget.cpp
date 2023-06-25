// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"

#include "CowPlayerController.h"
#include "Turret.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"




void USelectWidget::NativeConstruct()
{
	normalTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNormal);
	fireTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickFire);
	waterTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickWater);
	plantTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickPlant);

	targetPreviousButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickPrevious);
	targetNextButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNext);
	targetCloseButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickClose);

	cowPlayer = Cast<ACowPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	//cowPlayerPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

void USelectWidget::OnButtonClickNormal()
{
	cowPlayer->SetIsPlacingTurret(true, EElements::None);
}

void USelectWidget::OnButtonClickFire()
{
	cowPlayer->SetIsPlacingTurret(true, EElements::Fire);
}

void USelectWidget::OnButtonClickWater()
{
	cowPlayer->SetIsPlacingTurret(true, EElements::Water);
}

void USelectWidget::OnButtonClickPlant()
{
	cowPlayer->SetIsPlacingTurret(true, EElements::Plant);
}

void USelectWidget::OnButtonClickPrevious()
{
	if (cowPlayer->GetSelectedTurret() == nullptr)
	{
		return;
	}
	
	switch (cowPlayer->GetSelectedTurret()->Target)
	{
	case 0:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Plant;
		targetText->SetText(FText::FromString("Plant"));
		break;
	case 1:
		cowPlayer->GetSelectedTurret()->Target = TargetType::First;
		targetText->SetText(FText::FromString("First"));
		break;
	case 2:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Last;
		targetText->SetText(FText::FromString("Last"));
		break;
	case 3:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Fire;
		targetText->SetText(FText::FromString("Fire"));
		break;
	case 4:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Water;
		targetText->SetText(FText::FromString("Water"));
		break;
	}
}

void USelectWidget::OnButtonClickNext()
{
	if (cowPlayer->GetSelectedTurret() == nullptr)
	{
		return;
	}
	switch (cowPlayer->GetSelectedTurret()->Target)
	{
	case 0:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Last;
		targetText->SetText(FText::FromString("Last"));
		break;
	case 1:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Fire;
		targetText->SetText(FText::FromString("Fire"));
		break;
	case 2:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Water;
		targetText->SetText(FText::FromString("Water"));
		break;
	case 3:
		cowPlayer->GetSelectedTurret()->Target = TargetType::Plant;
		targetText->SetText(FText::FromString("Plant"));
		break;
	case 4:
		cowPlayer->GetSelectedTurret()->Target = TargetType::First;
		targetText->SetText(FText::FromString("First"));
		break;
	}
}

void USelectWidget::OnButtonClickClose()
{
	targetCanvasPanel->SetVisibility(ESlateVisibility::Hidden);
}

void USelectWidget::SetMilkText(int amount)
{
	FString numString = FString::FromInt(amount);
	FText numText = FText::FromString(numString);
	UTextBlock* hola = milkText;
	milkText->SetText(numText);
}

void USelectWidget::SetKillsText(int amount)
{
	FString numString = FString::FromInt(amount);
	FText numText = FText::FromString(numString);

	killsText->SetText(numText);
}

void USelectWidget::UpdateLifeBar(float percent)
{
	lifeBar->SetPercent(percent);
}