// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* rootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootCmp);

	staticMeshTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("static Mesh Turret"));
	staticMeshTurret->SetupAttachment(rootCmp);

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("box Collider"));
	boxCollider->SetupAttachment(rootCmp);

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("sphere Collider"));
	sphereCollider->SetupAttachment(rootCmp);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

