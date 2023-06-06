// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CowerDefense/ObjectPooler/PoolerObjects.h"

#include "GameModeLevel1.generated.h"

/**
 * 
 */
UCLASS()
class COWERDEFENSE_API AGameModeLevel1 : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly,Category = SpawnPool)
	APoolerObjects* spawnPool {nullptr};


public:

	APoolerObjects* GetSpawnPool() { return spawnPool; }
	void SetSpawnPool(APoolerObjects* pool) { spawnPool = pool; }

};