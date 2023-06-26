// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStats.h"
#include "CowerDefense/GameModes/GameModeLevel1.h"
#include "CowGameMode.h"
#include "CowerDefense/SelectWidget.h"
#include "Engine/World.h"


// Sets default values
AGameStats::AGameStats()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGameStats::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    if (AGameModeLevel1* gameMode = Cast<AGameModeLevel1>(GetWorld()->GetAuthGameMode(  )))
    {
        gameMode->SetGameStats(this);
    }
    if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
    {
        
        gameMode->SetGameStats(this);
    }
}

// Called when the game starts or when spawned
void AGameStats::BeginPlay()
{
	Super::BeginPlay();
	
    life = maxLife;

}


// Called every frame
void AGameStats::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameStats::GetDamage(float damage)
{
    life -= damage;
    float percent = life  / maxLife;
    if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
    {
        USelectWidget* widget = gameMode->GetPlayer()->selectWidgetInstance;
        widget->UpdateLifeBar(percent);
        if (life <= 0)
        {
            widget->OnLoseGame();
        }
    }

}

bool AGameStats::SpendMoney(float money)
{
    if (money > milk)
        return false;

    milk -= money;
    if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
    {
        USelectWidget* widget = gameMode->GetPlayer()->selectWidgetInstance;
        widget->SetMilkText(milk);
    }    
    return true;
}
void AGameStats::OnKillEnemy()
{
    totalKills++;
    float bonus =FMath::RandRange(7, 13);
    milk += bonus;
    if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
    {
        USelectWidget* widget = gameMode->GetPlayer()->selectWidgetInstance;
        widget->SetKillsText(totalKills);
        widget->SetMilkText(milk);
    }
    if (totalKills >= totalEnemies)
    {
        if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
        {
            gameMode->GetUIWidget()->WinGame();
        }
    }
}

