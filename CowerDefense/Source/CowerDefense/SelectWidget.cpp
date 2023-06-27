// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"

#include "Turret.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Animation/WidgetAnimation.h"
#include "CowGameMode.h"


void USelectWidget::NativeConstruct()
{
	normalTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNormal);
	fireTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickFire);
	waterTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickWater);
	plantTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickPlant);

	targetPreviousButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickPrevious);
	targetNextButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNext);
	targetCloseButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickClose);
	targetSellButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickSell);
	startWaveButton->OnClicked.AddDynamic(this, &USelectWidget::StartWave);
	goMenuButton->OnClicked.AddDynamic(this, &USelectWidget::GOMenu);
	goMenuButton->SetVisibility(ESlateVisibility::Hidden);
	
	cowPlayer = Cast<ACowPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	StoreWidgetAnimations();
	nextWaveAnimation = GetAnimationByName(TEXT("nextWaveAnim"));
	winOrLoseAnimation = GetAnimationByName(TEXT("winOrLoseAnimation"));
	if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
	{

		gameMode->SetUIWidget(this);
	}
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

void USelectWidget::OnButtonClickSell()
{
	cowPlayer->SellTurret();
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
void USelectWidget::StartWave()
{
	if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
	{
		gameMode->GetWaveManager()->StartWave();
	}
	startWaveButton->SetVisibility(ESlateVisibility::Hidden);
	startWaveButton->SetIsEnabled(false);
	NextWave();
}

void USelectWidget::NextWave()
{
	currentWave++;
	PlayAnimation(nextWaveAnimation);
}

void USelectWidget::SetWaveText()
{
	waveText->SetText(FText::FromString(FString::Printf(TEXT("Wave %d"), currentWave)));
}

void USelectWidget::StoreWidgetAnimations()
{
	AnimationMap.Empty();
	UProperty* prop = GetClass()->PropertyLink;

	while (prop)
	{
		if (prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* objProp = Cast<UObjectProperty>(prop);

			if (objProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* obj = objProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* widgetAnimation = Cast<UWidgetAnimation>(obj);
				if (widgetAnimation && widgetAnimation->MovieScene)
				{
					FName animname = widgetAnimation->MovieScene->GetFName();
					AnimationMap.Add(animname, widgetAnimation);
				}
			}
		}
		prop = prop->PropertyLinkNext;
	}
}

void USelectWidget::GOMenu()
{
	FName menuName = "MainMenu";
	UGameplayStatics::OpenLevel(GetWorld(), menuName);
}

UWidgetAnimation* USelectWidget::GetAnimationByName(FName AnimationName)const
{
	UWidgetAnimation* const* widgetAnimation = AnimationMap.Find(AnimationName);
	if (widgetAnimation)
	{
		return *widgetAnimation;
	}
	
	return nullptr;
}
void USelectWidget::WinGame()
{
	goMenuButton->SetVisibility(ESlateVisibility::Visible);
	winOrLoseText->SetText(FText::FromString("YOU WIN"));
	PlayAnimation(winOrLoseAnimation);
}
void USelectWidget::OnLoseGame()
{
	goMenuButton->SetVisibility(ESlateVisibility::Visible);
	winOrLoseText->SetText(FText::FromString("YOU LOSE"));
	PlayAnimation(winOrLoseAnimation);
}
