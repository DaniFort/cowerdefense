// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	timeToFinish = splinePath->GetSplineLength() / moveSpeed;
	timeProgression = 0;
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeProgression += GetWorld()->GetDeltaSeconds();
	follow_path();
}

void ABaseEnemy::follow_path()
{
	float alpha = timeProgression / timeToFinish;
	float splineLenght = splinePath->GetSplineLength();

	FVector newPosition = splinePath->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, splineLenght, alpha), ESplineCoordinateSpace::World);
	SetActorLocation(newPosition);
}

