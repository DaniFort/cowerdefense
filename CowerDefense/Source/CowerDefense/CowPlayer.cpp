// Fill out your copyright notice in the Description page of Project Settings.

#include "CowPlayer.h"

#include "SelectWidget.h"
#include "Turret.h"
#include "Camera/CameraComponent.h"
#include "Components/Button.h"
#include "Components/SphereComponent.h"
#include "Turret.h"
#include "CowGameMode.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "CowerDefense/ObjectPooler/PoolerObjects.h"


// Sets default values
ACowPlayer::ACowPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->SetupAttachment(RootComponent);

	playerCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	playerCollider->SetupAttachment(RootComponent);
}

void ACowPlayer::SetIsPlacingTurret(bool bIsPlacing, EElements elementType)
{
	isPlacingTurret = bIsPlacing;
	turretElement = elementType;
}

// Called when the game starts or when spawned
void ACowPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	cowPC->SetShowMouseCursor(true);
	selectWidgetInstance = CreateWidget<USelectWidget>(GetWorld(), selectWidget);
	selectWidgetInstance->AddToViewport();
	
	normalTurretInstance =  GetWorld()->SpawnActor<ATurret>(normalTurret, GetActorTransform());
	normalTurretInstance->SetActorScale3D(FVector(1,1,1));
	normalTurretInstance->SetActorRotation(FQuat::Identity);
	normalTurretInstance->SetActorEnableCollision(false);
	normalTurretInstance->SetIsActive(false);

	fireTurretInstance =  GetWorld()->SpawnActor<ATurret>(fireTurret, GetActorTransform());
	fireTurretInstance->SetActorScale3D(FVector(1,1,1));
	fireTurretInstance->SetActorRotation(FQuat::Identity); 
	fireTurretInstance->SetActorEnableCollision(false);                                          
	fireTurretInstance->SetIsActive(false);

	waterTurretInstance =  GetWorld()->SpawnActor<ATurret>(waterTurret, GetActorTransform());
	waterTurretInstance->SetActorScale3D(FVector(1,1,1));
	waterTurretInstance->SetActorRotation(FQuat::Identity); 
	waterTurretInstance->SetActorEnableCollision(false);                                          
	waterTurretInstance->SetIsActive(false);

	plantTurretInstance =  GetWorld()->SpawnActor<ATurret>(plantTurret, GetActorTransform());
	plantTurretInstance->SetActorScale3D(FVector(1,1,1));
	plantTurretInstance->SetActorRotation(FQuat::Identity); 
	plantTurretInstance->SetActorEnableCollision(false);                                          
	plantTurretInstance->SetIsActive(false);                                                      
}

// Called every frame
void ACowPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (isPlacingTurret)
	{
		PlaceTurret();
		selectWidgetInstance->normalTurretButton->SetVisibility(ESlateVisibility::Hidden);
		selectWidgetInstance->fireTurretButton->SetVisibility(ESlateVisibility::Hidden);
		selectWidgetInstance->waterTurretButton->SetVisibility(ESlateVisibility::Hidden);
		selectWidgetInstance->plantTurretButton->SetVisibility(ESlateVisibility::Hidden);
		
	}
	else
	{
		selectWidgetInstance->normalTurretButton->SetVisibility(ESlateVisibility::Visible);
		selectWidgetInstance->fireTurretButton->SetVisibility(ESlateVisibility::Visible);
		selectWidgetInstance->waterTurretButton->SetVisibility(ESlateVisibility::Visible);
		selectWidgetInstance->plantTurretButton->SetVisibility(ESlateVisibility::Visible);
		normalTurretInstance->SetActorHiddenInGame(true);
		fireTurretInstance->SetActorHiddenInGame(true);    
		waterTurretInstance->SetActorHiddenInGame(true);   
		plantTurretInstance->SetActorHiddenInGame(true);   
	}
}

// Called to bind functionality to input
void ACowPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &ACowPlayer::Move);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ACowPlayer::SpawnTurret);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ACowPlayer::SelectTurret);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ACowPlayer::ExitPlaceTurret);
}

void ACowPlayer::Move(float horizontalMovement)
{
	
	if (horizontalMovement > 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("horizontal"));
	}
}

void ACowPlayer::PlaceTurret()
{
	FVector playerLocation;
	FRotator rotation;
	
	GetController()->GetPlayerViewPoint(playerLocation, rotation);
	FVector mouseLocation;
	FVector worldDirection;
	
	UGameplayStatics::GetPlayerController(GetWorld(),0)->DeprojectMousePositionToWorld(mouseLocation,worldDirection);

	mouseLocation *= 5000000.f;
	worldDirection *= 50000000.f;
	
	FCollisionQueryParams traceParams;
	GetWorld()->LineTraceSingleByChannel(hit, playerLocation, worldDirection, ECC_Visibility, traceParams);
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *hit.Location.ToString());
	
	DrawDebugLine(GetWorld(), playerLocation, worldDirection, FColor::Black, false, 2.f);

	switch (turretElement)
	{
	case 0:
		normalTurretInstance->SetActorHiddenInGame(false);
		normalTurretInstance->SetActorLocation(hit.Location);
		break;

	case 1:
		fireTurretInstance->SetActorHiddenInGame(false);
		fireTurretInstance->SetActorLocation(hit.Location);
		break;
		
	case 2:
		waterTurretInstance->SetActorHiddenInGame(false);
		waterTurretInstance->SetActorLocation(hit.Location);
		break;

	case 3:
		plantTurretInstance->SetActorHiddenInGame(false);
		plantTurretInstance->SetActorLocation(hit.Location);
		break;
	}
	
	
}

void ACowPlayer::SpawnTurret()
{
	if (!isPlacingTurret)
	{
		return;
	}
	
	FTransform tempTransform;
	tempTransform.SetLocation(hit.Location);
	tempTransform.SetRotation(FQuat(FRotator(0,0,0)));
	//ATurret* tempTurret = GetWorld()->SpawnActor<ATurret>(normalTurret, tempTransform);

	ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode());
	APoolerObjects* pool = Cast<APoolerObjects>(gameMode->GetSpawnPool());
	AActor* newItem = nullptr;

	switch (turretElement)
	{
	case 0:
		newItem = pool->SpawnActor(normalTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();
		}
		break;

	case 1:
		newItem = pool->SpawnActor(fireTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();
		}
		break;

	case 2:
		newItem = pool->SpawnActor(waterTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();

		}
		break;

	case 3:
		newItem = pool->SpawnActor(plantTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();
		}
		break;
	}
	
	
	isPlacingTurret = false;
}

void ACowPlayer::ExitPlaceTurret()
{
	if (!isPlacingTurret)
	{
		return;
	}

	isPlacingTurret = false;
}

void ACowPlayer::SelectTurret()
{
	if (isPlacingTurret)
	{
		return;
	}
	
	FVector playerLocation;
	FRotator rotation;
	
	GetController()->GetPlayerViewPoint(playerLocation, rotation);
	FVector mouseLocation;
	FVector worldDirection;
	
	UGameplayStatics::GetPlayerController(GetWorld(),0)->DeprojectMousePositionToWorld(mouseLocation,worldDirection);

	mouseLocation *= 5000000.f;
	worldDirection *= 50000000.f;
	
	FCollisionQueryParams traceParams;
	GetWorld()->LineTraceSingleByChannel(hit, playerLocation, worldDirection, ECC_Visibility, traceParams);
	
	

	if (ATurret* turretSelected = Cast<ATurret>(hit.GetActor()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Objeto seleccionado: %s"), *turretSelected->GetName());
		//DrawDebugLine(GetWorld(), playerLocation, worldDirection, FColor::Black, false, 2.f);
		selectedTurret = turretSelected;
		switch (selectedTurret->Target)
		{
		case 0:
			selectWidgetInstance->targetText->SetText(FText::FromString("First"));
			break;
		case 1:
			selectWidgetInstance->targetText->SetText(FText::FromString("Last"));
			break;
		case 2:
			selectWidgetInstance->targetText->SetText(FText::FromString("Fire"));
			break;
		case 3:
			selectWidgetInstance->targetText->SetText(FText::FromString("Water"));
			break;
		case 4:
			selectWidgetInstance->targetText->SetText(FText::FromString("Plant"));
			break;
		}
		selectWidgetInstance->targetCanvasPanel->SetVisibility(ESlateVisibility::Visible);
	}
}

