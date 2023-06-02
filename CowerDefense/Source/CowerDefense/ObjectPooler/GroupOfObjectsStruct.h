// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"



#include"GroupOfObjectsStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COWERDEFENSE_API FGroupOfObjectsStruct
{
public:

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int amount;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> objectsToPool;


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> classType;
	//UPROPERTY(EditAnywhere)
	//UClass* classType;
	//UPROPERTY(EditAnywhere)
	//UObject* classType;



	FGroupOfObjectsStruct();
	~FGroupOfObjectsStruct();
};
