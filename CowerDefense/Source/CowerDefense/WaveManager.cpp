// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "CowerDefense/GameModes/GameModeLevel1.h"
#include "Components/SplineComponent.h"


#include "CowerDefense/ObjectPooler/PoolerObjects.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	if (AGameModeLevel1* gameMode = Cast<AGameModeLevel1>(GetWorld()->GetAuthGameMode()))
	{
		pool = gameMode->GetSpawnPool();
	}
	
	SetActorTickEnabled(false);

	if (waveOrder.Num()>0 )
	{
		elapsedTime = waveOrder[currentWave].enemyOrder[waveOrder[currentWave].currentEnemy].Y;
	}

}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime -= GetWorld()->GetDeltaSeconds();

	FString FloatAsString = FString::SanitizeFloat(elapsedTime);
	//GEngine->AddOnScreenDebugMessage(5, 1, FColor::Red, FloatAsString);

	if (elapsedTime <= 0)
	{
		SpawnEnemy();
	}
}

void AWaveManager::SpawnEnemy()
{
	if (waveOrder.Num() == 0)
		return;

	FBaseWave* runingWave = &waveOrder[currentWave];

	int idEnemyType = runingWave->enemyOrder[runingWave->currentEnemy].X; // buscar tipo de enemigo

	//UClass* clasToSpawn = enemyTypes[idEnemyType];//coger la clase de ese
	//
	//AActor* newEnemy = pool->SpawnActor(clasToSpawn, initPosition, initRotation);
	//if (ClaseEnemigo* enemyPath = Cast<ClaseEnemigo>(newEnemy))
	//{
	//	enemyPath->splinePath = splinePath;
	//}

	elapsedTime = runingWave->enemyOrder[runingWave->currentEnemy].Y;


	runingWave->currentEnemy++;


	if (runingWave->IsWaveFinished())
	{
		//acabar oleada
		currentWave++;
		if (currentWave >= waveOrder.Num())
		{
			SetActorTickEnabled(false);
		}
		NextWave();
		return;
	}

}

void AWaveManager::StartWave()
{
	SetActorTickEnabled(true);
}


void AWaveManager::NextWave()
{
	//cosas de texto y esas cosas
}