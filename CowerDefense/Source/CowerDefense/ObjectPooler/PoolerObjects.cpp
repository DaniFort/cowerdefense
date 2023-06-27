// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolerObjects.h"
#include "CowerDefense/GameModes/GameModeLevel1.h"
#include "CowerDefense/CowGameMode.h"
#include "GameFrameWork/Character.h"

// Sets default values
APoolerObjects::APoolerObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

void APoolerObjects::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    if (AGameModeLevel1* gameMode = Cast<AGameModeLevel1>(GetWorld()->GetAuthGameMode()))
    {
        gameMode->SetSpawnPool(this);
    }
    if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
    {
        gameMode->SetSpawnPool(this);
    }
}

// Called when the game starts or when spawned
void APoolerObjects::BeginPlay()
{
	Super::BeginPlay();

	FVector startPos(0, 0, 30000.f);
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
                newActor->SetActorLocation(startPos);
            }
            else
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                newActor = GetWorld()->SpawnActor<AActor>(currentClass,SpawnParams);
                newActor->SetActorLocation(startPos);
            }
        

            group.objectsToPool.Add(newActor);
            DespawnActor(newActor);

        }
    }
    
}

AActor* APoolerObjects::SpawnActor(UClass* actorType, FVector Position, FRotator Rotation)
{
    for (FGroupOfObjectsStruct& group : objects)
    {
        UClass* groupClass = group.classType;
        //UClass* actorClass = actorType->GetClass();

        if (groupClass == actorType)
        {
            for (AActor* actor : group.objectsToPool)
            {
                if (actor->IsHidden())
                {
                    actor->SetActorLocation(Position);
                    actor->SetActorRotation(Rotation);
                    Cast<IPooledObject>(actor)->Spawn();
                    return actor;
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
            Cast<IPooledObject>(newActor)->Spawn();
            newActor->SetActorLocation(Position);
            newActor->SetActorRotation(Rotation);
            group.objectsToPool.Add(newActor);
            return newActor;

        }
    }
    return NULL;
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
