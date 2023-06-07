// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"

#include "Components/Button.h"

void USelectWidget::NativeConstruct()
{
	normalTurretButton->OnClicked.AddDynamic(this, &USelectWidget::OnButtonClickNormal);
}

void USelectWidget::OnButtonClickNormal()
{
	UE_LOG(LogTemp, Log, TEXT("BOTON"));
}

