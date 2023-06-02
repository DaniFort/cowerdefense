// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDePruebasEsInutil.h"

// Sets default values
ACharacterDePruebasEsInutil::ACharacterDePruebasEsInutil()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterDePruebasEsInutil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterDePruebasEsInutil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterDePruebasEsInutil::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterDePruebasEsInutil::Spawn()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(false);
}
void ACharacterDePruebasEsInutil::Despawn()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(true);
}

