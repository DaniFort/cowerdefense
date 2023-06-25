// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CowerDefense/ObjectPooler/PoolerObjects.h"
#include "CowerDefense/GameStats.h"
#include "CowerDefense/SelectWidget.h"
#include "CowGameMode.generated.h"



UCLASS()
class COWERDEFENSE_API ACowGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
		APoolerObjects* spawnPool {
		nullptr
	};


	UPROPERTY()
		AGameStats* gameStats {
		nullptr
	};

	USelectWidget* widgetUI{ nullptr };

public:

	APoolerObjects* GetSpawnPool() { return spawnPool; }
	void SetSpawnPool(APoolerObjects* pool) { spawnPool = pool; }

	AGameStats* GetGameStats() { return gameStats; }
	void SetGameStats(AGameStats* stats) { gameStats = stats; }

	USelectWidget* GetUIWidget() { return widgetUI; }
	void SetUIWidget(USelectWidget* widget) { widgetUI = widget; }
	
};
