// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	playButton->OnClicked.AddDynamic(this, &UMainMenu::OnButtonClickPlay);
}

void UMainMenu::OnButtonClickPlay()
{
	levelToLoad = "L_Level01";
	const FLatentActionInfo latentInfo;
	//UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, latentInfo);
	UGameplayStatics::OpenLevel(this, levelToLoad);
}
