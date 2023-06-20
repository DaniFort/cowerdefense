// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "CowerDefense/GameModes/GameModeLevel1.h"
#include "Components/SplineComponent.h"
#include "CowerDefense/Enemies/BaseEnemy.h"
#include "CowGameMode.h"

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
	if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
	{
		pool = gameMode->GetSpawnPool();
	}
	
	SetActorTickEnabled(false);

	if (waveOrder.Num()>0 )
	{
		elapsedTime = waveOrder[currentWave].enemyOrder[waveOrder[currentWave].currentEnemy].Y;
	}
	//splinePath = splineParent->FindComponentByClass<USplineComponent>();

	if (USplineComponent* spline = splineParent->FindComponentByClass<USplineComponent>())
	{
		splinePath = spline;
	}


}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	elapsedTime -= GetWorld()->GetDeltaSeconds();

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

	UClass* clasToSpawn = enemyTypes[idEnemyType];//coger la clase de ese
	
	AActor* newEnemy = pool->SpawnActor(clasToSpawn, initPosition, initRotation);
	if (ABaseEnemy* enemyPath = Cast<ABaseEnemy>(newEnemy))
	{
		enemyPath->SetSplinePath(splinePath);
	}

	elapsedTime = runingWave->enemyOrder[runingWave->currentEnemy].Y;


	runingWave->currentEnemy++;


	if (runingWave->IsWaveFinished())
	{
		//acabar oleada
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
	currentWave++;
	if (currentWave >= waveOrder.Num())
	{
		SetActorTickEnabled(false);
	}
	else
	{
		//fin juego 
	}
	GEngine->AddOnScreenDebugMessage(5, elapsedTime, FColor::Orange, "NEXT WAVE");
	//meter texto por ptantalla
	//cosas de texto y esas cosas
}