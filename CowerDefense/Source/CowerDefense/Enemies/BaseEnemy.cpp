// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/SplineComponent.h"
#include "Engine/SplineMeshActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isAlive = true;
	skeletalMeshEnemy = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("static mesh enemy"));
	skeletalMeshEnemy->SetupAttachment(RootComponent);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (!splinePath)
		return;
	isAlive = true;
	timeToFinish = splinePath->GetSplineLength() / moveSpeed;
	timeProgression = 0;
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAlive == false)
		return;
	if (health <= 0)
		isAlive = false;

	timeProgression += DeltaTime;
	follow_path();
}

void ABaseEnemy::follow_path()
{
	float alpha = timeProgression / timeToFinish;
	float splineLenght = splinePath->GetSplineLength();
	
	FVector newPosition = splinePath->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, splineLenght, alpha), ESplineCoordinateSpace::World);
	FRotator newRotation = splinePath->GetRotationAtDistanceAlongSpline(FMath::Lerp(0, splineLenght, alpha), ESplineCoordinateSpace::World);
	SetActorLocation(newPosition);
	SetActorRotation(newRotation);
}