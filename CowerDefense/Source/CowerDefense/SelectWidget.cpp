// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"

#include "CowPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USelectWidget::NativeConstruct()
{
	normalTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNormal);
}

void USelectWidget::OnButtonClickNormal()
{
	UE_LOG(LogTemp, Log, TEXT("BOTON"));
	
	cowPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	cowPlayerPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	cowPlayerPC->SetPlayerBool(true);
	
}

