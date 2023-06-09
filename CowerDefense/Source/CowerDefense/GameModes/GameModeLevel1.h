// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CowerDefense/ObjectPooler/PoolerObjects.h"
#include "CowerDefense/GameStats.h"

#include "GameModeLevel1.generated.h"

/**
 * 
 */
UCLASS()
class COWERDEFENSE_API AGameModeLevel1 : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	APoolerObjects* spawnPool {nullptr};


	UPROPERTY()
		AGameStats* gameStats {nullptr};


public:

	APoolerObjects* GetSpawnPool() { return spawnPool; }
	void SetSpawnPool(APoolerObjects* pool) { spawnPool = pool; }

	AGameStats* GetGameStats() { return gameStats; }
	void SetGameStats(AGameStats* stats) { gameStats = stats; }

};