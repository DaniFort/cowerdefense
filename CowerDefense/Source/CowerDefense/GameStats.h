// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameStats.generated.h"

class USelectWidget;
UCLASS()
class COWERDEFENSE_API AGameStats : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameStats();

protected:
	virtual void PreInitializeComponents()override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//variables
	UPROPERTY(EditAnywhere)
	float milk{ 100 };
	UPROPERTY(EditAnywhere)
	float maxLife{ 100 };
	float life{ 0 };
	int totalKills{ 0 };
	int totalEnemies{ 0 };
	
	USelectWidget* widgetUI{ nullptr };


	void GetDamage(float damage);
	float GetMilk() { return milk; }
	bool SpendMoney(float money);
	UFUNCTION(CallInEditor)
	void OnKillEnemy();

	UFUNCTION(CallInEditor)
		void MONEY() { SpendMoney(20); }
	UFUNCTION(CallInEditor)
		void DAMAGE(){ GetDamage(20); }
	


};
