// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "WaveManager.generated.h"

class APoolerObjects;
class USplineComponent;

USTRUCT(BlueprintType)
struct FBaseWave
{
	GENERATED_BODY()

		int32 currentEnemy {0};

	UPROPERTY(EditAnywhere)
		TArray<FVector2D> enemyOrder;
	bool IsWaveFinished()
	{
		return currentEnemy >= enemyOrder.Num() ? true : false;
	}
};


UCLASS()
class COWERDEFENSE_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//variables
	UPROPERTY(EditAnywhere)
	APoolerObjects* pool{nullptr};

	UPROPERTY(EditAnywhere)
	USplineComponent* splinePath{nullptr};

	//referencia al spline
	UPROPERTY(EditInstanceOnly)
	TArray<TSubclassOf<AActor>> enemyTypes;

	UPROPERTY(EditInstanceOnly)
	TArray<FBaseWave> waveOrder;



	int currentWave{ 0 };

	float elapsedTime{ 0 };

	UPROPERTY(EditAnywhere)
	FVector initPosition;

	UPROPERTY(EditAnywhere)
	FRotator initRotation;

	//functions
private:
	void SpawnEnemy();
	void NextWave();

public:
	void StartWave();

};
