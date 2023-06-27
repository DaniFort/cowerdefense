// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	playButton->OnClicked.AddDynamic(this, &UMainMenu::OnButtonClickPlay);
	exitButton->OnClicked.AddDynamic(this, &UMainMenu::OnButtonClickExit);
}

void UMainMenu::OnButtonClickPlay()
{
	levelToLoad = "L_Level01";
	const FLatentActionInfo latentInfo;
	//UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, latentInfo);
	UGameplayStatics::OpenLevel(this, levelToLoad);
}

void UMainMenu::OnButtonClickExit()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(),0), EQuitPreference::Quit, true);
}
