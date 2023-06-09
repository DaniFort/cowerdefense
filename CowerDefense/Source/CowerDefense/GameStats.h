// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameStats.generated.h"

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

	void GetDamage(float& damage);
	bool SpendMoney(float money);

};
