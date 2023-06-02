// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PooledObject.h"


#include "CharacterDePruebasEsInutil.generated.h"

UCLASS()
class COWERDEFENSE_API ACharacterDePruebasEsInutil : public ACharacter, public IPooledObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterDePruebasEsInutil();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Spawn()override;
	virtual void Despawn()override;

};
