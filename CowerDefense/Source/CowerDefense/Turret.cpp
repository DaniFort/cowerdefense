// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"

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

	USceneComponent* shootPoint0 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 0"));
	shootPoint0->SetupAttachment(pivotStaticMesh);
	USceneComponent* shootPoint1 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 1"));
	shootPoint1->SetupAttachment(pivotStaticMesh);
	USceneComponent* shootPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 2"));
	shootPoint2->SetupAttachment(pivotStaticMesh);
	USceneComponent* shootPoint3 = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Point 3"));
	shootPoint3->SetupAttachment(pivotStaticMesh);
	shootPoints.Add(shootPoint0);
	shootPoints.Add(shootPoint1);
	shootPoints.Add(shootPoint2);
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
	sphereCollider->SetSphereRadius(range);
}

#if WITH_EDITOR
void ATurret::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName().ToString() == FString("range"))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyChangedEvent.GetPropertyName().ToString());
		sphereCollider->SetSphereRadius(range);
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
	if (!enemiesDetected.IsEmpty() && enemiesDetected[0] != nullptr)
	{
		RotateTowardsEnemy(enemiesDetected[0]->GetActorLocation());
	}

}


void ATurret::RotateTowardsEnemy(FVector whereToLook)
{
	FRotator rotLookAt = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), enemiesDetected[0]->GetActorLocation());

	pivotStaticMesh->SetWorldRotation(rotLookAt);
}


void ATurret::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* enemyBeginHit = Cast<APawn>(OtherActor))
	{
		enemiesDetected.Add(enemyBeginHit);
		UE_LOG(LogTemp, Warning, TEXT("HOLA OK"));
	}
}

void ATurret::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APawn* enemyEndHit = Cast<APawn>(OtherActor))
	{
		enemiesDetected.Remove(enemyEndHit);
		UE_LOG(LogTemp, Warning, TEXT("ADIOS OK"));
	}
}

