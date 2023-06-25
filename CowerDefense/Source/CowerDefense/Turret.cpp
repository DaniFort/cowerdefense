// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include <string>

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Enemies/BaseEnemy.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* rootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootCmp);
	
	pivotStaticMesh = CreateDefaultSubobject<USceneComponent>(TEXT("pivot Static Mesh"));
	pivotStaticMesh->SetupAttachment(rootCmp);
	pivotStaticMesh->SetRelativeLocation(FVector (0.f,10.f,340.f));

	staticMeshTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("static Mesh Turret"));
	staticMeshTurret->SetupAttachment(pivotStaticMesh);
	staticMeshTurret->SetRelativeLocation(FVector (0.f,100.f,0.f));
	staticMeshTurret->SetRelativeScale3D(FVector (13.f,13.f,13.f));

	enemiesDetected.Reserve(5);

	shootPoint0 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 0"));
	shootPoint0->SetupAttachment(pivotStaticMesh);
	shootPoints.Add(shootPoint0);
	shootPoint1 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 1"));
	shootPoint1->SetupAttachment(pivotStaticMesh);
	shootPoints.Add(shootPoint1);
	shootPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 2"));
	shootPoint2->SetupAttachment(pivotStaticMesh);
	shootPoints.Add(shootPoint2);
	shootPoint3 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 3"));
	shootPoint3->SetupAttachment(pivotStaticMesh);
	shootPoints.Add(shootPoint3);
	
	staticMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("static Mesh Base"));
	staticMeshBase->SetupAttachment(rootCmp);
	staticMeshBase->SetRelativeLocation(FVector (0.f,0.f,50.f));
	staticMeshBase->SetRelativeScale3D(FVector (2.5f,2.5f,1.f));

	staticMeshStick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("static Mesh Stick"));
	staticMeshStick->SetupAttachment(rootCmp);
	staticMeshStick->SetRelativeLocation(FVector (0.f,0.f,120.f));
	staticMeshStick->SetRelativeScale3D(FVector (0.1f,0.1f,0.75f));
	
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("box Collider"));
	boxCollider->SetupAttachment(rootCmp);
	boxCollider->SetRelativeLocation(FVector (0.f,0.f,300.f));
	boxCollider->SetRelativeScale3D(FVector (3.f,3.f,7.f));

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("sphere Collider"));
	sphereCollider->SetupAttachment(rootCmp);
	sphereCollider->SetSphereRadius(maxRange);

	milkBeam = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Milk Beam"));
	milkBeam->SetupAttachment(rootCmp);
}

#if WITH_EDITOR
void ATurret::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName().ToString() == FString("maxRange"))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyChangedEvent.GetPropertyName().ToString());
		sphereCollider->SetSphereRadius(maxRange);
	}
	else if (PropertyChangedEvent.GetPropertyName().ToString() == FString("buyPrice"))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyChangedEvent.GetPropertyName().ToString());
		sellPrice = buyPrice * 0.75f;
	}
	else if (PropertyChangedEvent.GetPropertyName().ToString() == FString("sellPrice"))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyChangedEvent.GetPropertyName().ToString());
		buyPrice = sellPrice * 1.25f;
	}
	
}
#endif

void ATurret::EnableCollision()
{
	range = FMath::Lerp(0, maxRange, alphaCollision);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), range);
	if (range >= maxRange)
	{
		isEnablingCollision = false;
		range = maxRange;
	}
}

void ATurret::AttackEnemy()
{
	if (timeToAttack <= 0 && !enemiesDetected.IsEmpty() && enemyToAttack != nullptr)
	{
		if (enemyToAttack->GetElement() == Element) //Ambos iguales EMPATE == NADA
		{
			enemyToAttack->ReceiveDamage(attackPower);
		}
		else if(enemyToAttack->GetElement() == EElements::None && Element != EElements::None) //Si enemigo es none y torreta cualquiera que no sea none GANA
		{
			enemyToAttack->ReceiveDamage(attackPower * winMultiplier);
		}

		if(enemyToAttack->GetElement() == EElements::Fire && Element == EElements::Water) //Si enemigo es fuego y torreta agua GANA
		{
			enemyToAttack->ReceiveDamage(attackPower * winMultiplier);
		}
		else if(enemyToAttack->GetElement() == EElements::Water && Element == EElements::Plant) //Si enemigo es agua y torreta planta GANA
		{
			enemyToAttack->ReceiveDamage(attackPower * winMultiplier);
		}
		else if(enemyToAttack->GetElement() == EElements::Plant && Element == EElements::Fire) //Si enemigo es planta y torreta fuego GANA
		{
			enemyToAttack->ReceiveDamage(attackPower * winMultiplier);
		}
		else if(enemyToAttack->GetElement() != EElements::None) //Llegados a este punto, torreta es none. Si enemigo no es none, PIERDE
		{
			enemyToAttack->ReceiveDamage(attackPower * loseMultiplier);
		}
		UE_LOG(LogTemp, Warning, TEXT("Atacado"));
		ShootMilkBeam();
		timeToAttack = timeToAttackTotal;
	}
}

void ATurret::ActivateCollision()
{
	isEnablingCollision = true;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
	sphereCollider->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SelectEnemyToAttack();
	if (!enemiesDetected.IsEmpty() && enemiesDetected[0] != nullptr)
	{
		RotateTowardsEnemy();
	}

	if (isEnablingCollision)
	{
		EnableCollision();
		sphereCollider->SetSphereRadius(range, true);
		alphaCollision+= DeltaTime;
	}

	if (timeToAttack > 0)
	{
		timeToAttack -= attackVelocity * DeltaTime;
	}

	AttackEnemy();
}


void ATurret::RotateTowardsEnemy()
{
	FRotator rotLookAt = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), enemyToAttack->GetActorLocation());

	pivotStaticMesh->SetWorldRotation(rotLookAt);
}


void ATurret::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseEnemy* enemyBeginHit = Cast<ABaseEnemy>(OtherActor))
	{
		enemiesDetected.Add(enemyBeginHit);
	}
}

void ATurret::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseEnemy* enemyEndHit = Cast<ABaseEnemy>(OtherActor))
	{
		enemiesDetected.Remove(enemyEndHit);
	}
}

void ATurret::ShootMilkBeam()
{
	//milkBeam->Activate();
	//milkBeam->AddForce(FVector(0,1,0));
	DrawDebugLine(GetWorld(), shootPoint0->GetComponentLocation(), enemyToAttack->GetActorLocation(), FColor::White, false, .5f, 0, 10.f);
}

void ATurret::SelectEnemyToAttack()
{
	if (enemiesDetected.IsEmpty())
	{
		return;
	}

	enemyToAttack = nullptr;

	enemiesDetected.Sort([](const ABaseEnemy& enemyA, const ABaseEnemy& enemyB)
	{
		return enemyA.GetAlpha() > enemyB.GetAlpha();
	});
	
	switch (Target)
	{
	case 0: //First
		enemyToAttack = enemiesDetected[0];
		break;

	case 1: //Last
		enemyToAttack = enemiesDetected.Last();
		break;

	case 2: //Fire
		for (auto enemy : enemiesDetected)
		{
			if (enemy->GetElement() == EElements::Fire)
			{
				enemyToAttack = enemy;
				return;
			}
		}

		if (enemyToAttack == nullptr)
		{
			enemyToAttack = enemiesDetected[0];
		}
		
		break;

	case 3: //Water
		for (auto enemy : enemiesDetected)
		{
			if (enemy->GetElement() == EElements::Water)
			{
				enemyToAttack = enemy;
				return;
			}
		}
		
		if (enemyToAttack == nullptr)
		{
			enemyToAttack = enemiesDetected[0];
		}
		
		break;

	case 4: //Plant
		for (auto enemy : enemiesDetected)
		{
			if (enemy->GetElement() == EElements::Plant)
			{
				enemyToAttack = enemy;
				return;
			}
		}
		
		if (enemyToAttack == nullptr)
		{
			enemyToAttack = enemiesDetected[0];
		}
		
		break;
	}

}

void ATurret::Spawn()
{
	SetActorHiddenInGame(false);
	staticMeshTurret->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	staticMeshBase->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	staticMeshStick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorTickEnabled(true);


}
void ATurret::Despawn()
{
	SetActorHiddenInGame(true);
	staticMeshTurret->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	staticMeshBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	staticMeshStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorTickEnabled(false);

}