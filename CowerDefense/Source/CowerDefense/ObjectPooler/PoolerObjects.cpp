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

    for (FGroupOfObjectsStruct& group : objects)
    {
        //group.objectsToPool.Reserve(100);
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
            DespawnActor(newActor);

        }
    }
    
}



void APoolerObjects::SpawnActor(UClass* actorType, FVector Position, FRotator Rotation)
{
    for (FGroupOfObjectsStruct& group : objects)
    {
        UClass* groupClass = group.classType;
        //UClass* actorClass = actorType->GetClass();

        if (groupClass == actorType)
        {
            for (AActor* actor : group.objectsToPool)
            {
                if (!actor->IsHidden())
                {
                    actor->SetActorLocation(Position);
                    actor->SetActorRotation(Rotation);
                    Cast<IPooledObject>(actor)->Spawn();
                    return;
                }
            }
            //si no hubiese disponible creamos otro
            AActor* newActor = nullptr;

            if (!groupClass->IsChildOf(ACharacter::StaticClass()))
            {
                newActor = GetWorld()->SpawnActor<AActor>(groupClass);
            }
            else
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                newActor = GetWorld()->SpawnActor<AActor>(groupClass, SpawnParams);
            }

            newActor->SetActorLocation(Position);
            newActor->SetActorRotation(Rotation);
            group.objectsToPool.Add(newActor);

        }
    }


}

void APoolerObjects::DespawnActor(AActor* actorType)
{
    if (IPooledObject* actorInterface = Cast<IPooledObject>(actorType))
    {
        actorInterface->Despawn();
    }

    /*UClass* actorClass = actorType->GetClass();

    for (FGroupOfObjectsStruct& group : objects)
    {
        UClass* groupClass = group.classType;

        if (groupClass == actorClass)
        {
            Cast<IPooledObject>(actorType)->Despawn();
            return;
        }
    }*/
}
