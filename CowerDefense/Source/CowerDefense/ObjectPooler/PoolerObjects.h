// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//UNREAL
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//PROJECT
#include "GroupOfObjectsStruct.h"


#include "PoolerObjects.generated.h"



UCLASS()
class COWERDEFENSE_API APoolerObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolerObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//variables
public:
	UPROPERTY(EditAnywhere)
	TArray<FGroupOfObjectsStruct> objects;

	//functions
public:
	UFUNCTION()
	void SpawnActor(AActor*actor);
	UFUNCTION()
	void DespawnActor(AActor* actor);


};
