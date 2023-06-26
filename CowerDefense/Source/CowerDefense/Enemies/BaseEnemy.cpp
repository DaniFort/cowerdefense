// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/SplineComponent.h"
#include "Engine/SplineMeshActor.h"
#include "CowerDefense/CowGameMode.h"

#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"


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

	GetComponents<UNiagaraComponent>(NiagaraComponents);
	for (int i = 0; i < NiagaraComponents.Num(); i++)
	{
		NiagaraComponents[i]->SetActive(false);
	}
	isAlive = true;
	health = maxHealth;
	if (!splinePath)
		return;
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
	alpha = timeProgression / timeToFinish;
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
	ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode());
	gameMode->GetGameStats()->GetDamage(damageOnWin);

	Despawn();
}


void ABaseEnemy::ReceiveDamage(float damage)
{
	health -= damage;
	if (health <= 0)
	{
		if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
		{
			gameMode->GetGameStats()->OnKillEnemy();
		}
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

	int randElement = FMath::RandRange(0, 3);
	switch(randElement)
	{
	case 0:
		Element = EElements::None;
		break;
	case 1:
		Element = EElements::Water;
		NiagaraComponents[0]->SetActive(true);
		break;
	case 2:
		Element = EElements::Plant;
		NiagaraComponents[1]->SetActive(true);
		break;
	case 3:
		Element = EElements::Fire;
		NiagaraComponents[2]->SetActive(true);
		break;
	default:
		Element = EElements::None;
		break;
	}

}
void ABaseEnemy::Despawn()
{
	isAlive = false;
	SetActorHiddenInGame(true);
	boxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	skeletalMeshEnemy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorTickEnabled(false);
	for (int i = 0; i < NiagaraComponents.Num(); i++)
	{
		NiagaraComponents[i]->SetActive(false);
	}
}

void ABaseEnemy::SetSplinePath(USplineComponent* spline)
{
	splinePath = spline;
	float jsue = splinePath->GetSplineLength();
	FString hola = FString::SanitizeFloat(jsue);
	//GEngine->AddOnScreenDebugMessage(5, 1, FColor::Blue, hola);
	boxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	timeToFinish = splinePath->GetSplineLength() / moveSpeed;
	timeProgression = 0;
}