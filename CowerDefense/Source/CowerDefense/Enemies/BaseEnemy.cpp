// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/SplineComponent.h"
#include "Engine/SplineMeshActor.h"
#include "CowerDefense/GameModes/GameModeLevel1.h"

#include "Components/BoxComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isAlive = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	SetRootComponent(root);

	skeletalMeshEnemy = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("static mesh enemy"));
	skeletalMeshEnemy->SetupAttachment(root);

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	boxCollider->SetupAttachment(root);
	//skeletalMeshEnemy->SetRelativeRotation()
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (!splinePath)
		return;
	isAlive = true;
	health = maxHealth;

}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAlive == false)
		return;



	timeProgression += DeltaTime;
	follow_path();

}

void ABaseEnemy::follow_path()
{
	float alpha = timeProgression / timeToFinish;
	float splineLenght = splinePath->GetSplineLength();
	
	//FString hola = FString::SanitizeFloat(alpha);
	//GEngine->AddOnScreenDebugMessage(5, 1, FColor::Blue, hola);

	FVector newPosition = splinePath->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, splineLenght, alpha), ESplineCoordinateSpace::World);
	FRotator newRotation = splinePath->GetRotationAtDistanceAlongSpline(FMath::Lerp(0, splineLenght, alpha), ESplineCoordinateSpace::World);
	SetActorLocation(newPosition);
	SetActorRotation(newRotation);

	if (alpha >= 1)
		ReachEnd();
}
void ABaseEnemy::ReachEnd()
{
	AGameModeLevel1* gameMode = Cast<AGameModeLevel1>(GetWorld()->GetAuthGameMode());
	gameMode->GetGameStats()->GetDamage(damageOnWin);

	Despawn();
}


void ABaseEnemy::OnGetDamage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		Despawn();
	}
}



void ABaseEnemy::Spawn()
{
	isAlive = true;
	SetActorHiddenInGame(false);
	skeletalMeshEnemy->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorTickEnabled(true);
	health = maxHealth;


}
void ABaseEnemy::Despawn()
{
	isAlive = false;
	SetActorHiddenInGame(true);
	skeletalMeshEnemy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorTickEnabled(false);

}

void ABaseEnemy::SetSplinePath(USplineComponent* spline)
{
	splinePath = spline;
	float jsue = splinePath->GetSplineLength();
	FString hola = FString::SanitizeFloat(jsue);
	GEngine->AddOnScreenDebugMessage(5, 1, FColor::Blue, hola);

	timeToFinish = splinePath->GetSplineLength() / moveSpeed;
	timeProgression = 0;
}