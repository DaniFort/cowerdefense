// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"

#include "CowPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"

void USelectWidget::NativeConstruct()
{
	normalTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNormal);
	fireTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickFire);
	waterTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickWater);
	plantTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickPlant);

}

void USelectWidget::OnButtonClickNormal()
{
	UE_LOG(LogTemp, Log, TEXT("BOTON NORMAL"));
	
	cowPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	cowPlayerPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	cowPlayerPC->SetPlayerBool(true, EElements::None);
	
}

void USelectWidget::OnButtonClickFire()
{
	UE_LOG(LogTemp, Log, TEXT("BOTON FIRE"));
	
	cowPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	cowPlayerPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	cowPlayerPC->SetPlayerBool(true, EElements::Fire);
}

void USelectWidget::OnButtonClickWater()
{
	UE_LOG(LogTemp, Log, TEXT("BOTON WATER"));
	
	cowPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	cowPlayerPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	cowPlayerPC->SetPlayerBool(true, EElements::Water);
}

void USelectWidget::OnButtonClickPlant()
{
	UE_LOG(LogTemp, Log, TEXT("BOTON PLANT"));
	
	cowPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	cowPlayerPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	cowPlayerPC->SetPlayerBool(true, EElements::Plant);
}

void USelectWidget::SetMilkText(int amount)
{
	FString numString = FString::FromInt(amount);
	FText numText = FText::FromString(numString);

	milkText->SetText(numText);
}

void USelectWidget::SetKillsText(int amount)
{
	FString numString = FString::FromInt(amount);
	FText numText = FText::FromString(numString);

	killsText->SetText(numText);
}

