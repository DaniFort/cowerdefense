// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolerObjects.h"

#include "GameFrameWork/Character.h"

// Sets default values
APoolerObjects::APoolerObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

// Called when the game starts or when spawned
void APoolerObjects::BeginPlay()
{
	Super::BeginPlay();

	FVector startPos(0, 0, 0);
    FActorSpawnParameters SpawnInfo;
    FRotator myRot(0, 0, 0);

    for (FGroupOfObjectsStruct& group : objects)//igual hay que quitar el const
    {
        group.objectsToPool.Reserve(100);
        UClass* currentClass = group.classType;
        for (int32 i = 0; i < group.amount; i++)
        {
            AActor* newActor = nullptr;

            if (!currentClass->IsChildOf(ACharacter::StaticClass()))
            {
                newActor = GetWorld()->SpawnActor<AActor>(currentClass);
            }
            else
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                newActor = GetWorld()->SpawnActor<AActor>(currentClass,SpawnParams);
            }


            group.objectsToPool.Add(newActor);
        }
    }
}



void APoolerObjects::SpawnActor(AActor* actorType)
{

}

void APoolerObjects::DespawnActor(AActor* actorType)
{

}
