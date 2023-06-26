// Fill out your copyright notice in the Description page of Project Settings.

#include "CowPlayer.h"

#include "SelectWidget.h"
#include "Turret.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "CowGameMode.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "CowerDefense/ObjectPooler/PoolerObjects.h"
#include "GameStats.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACowPlayer::ACowPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArm->SetupAttachment(RootComponent);

	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->SetupAttachment(springArm);

	playerCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	playerCollider->SetupAttachment(RootComponent);
}

void ACowPlayer::SetIsPlacingTurret(bool bIsPlacing, EElements elementType)
{
	isPlacingTurret = bIsPlacing;
	turretElement = elementType;
}
void ACowPlayer::PreInitializeComponents()
{
	if (ACowGameMode* gameMode = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode()))
	{
		gameMode->SetPlayer(this);
	}
}

// Called when the game starts or when spawned
void ACowPlayer::BeginPlay()
{
	Super::BeginPlay();
	cowGM = Cast<ACowGameMode>(GetWorld()->GetAuthGameMode());
	gameStats = cowGM->GetGameStats();
	
	cowPC->SetShowMouseCursor(true);
	selectWidgetInstance = CreateWidget<USelectWidget>(GetWorld(), selectWidget);
	selectWidgetInstance->AddToViewport();
	
	normalTurretInstance = GetWorld()->SpawnActor<ATurret>(normalTurret, GetActorTransform());
	normalTurretInstance->SetActorScale3D(FVector(1,1,1));
	normalTurretInstance->SetActorRotation(FQuat::Identity);
	normalTurretInstance->SetActorEnableCollision(false);
	normalTurretInstance->SetIsActive(false);

	fireTurretInstance = GetWorld()->SpawnActor<ATurret>(fireTurret, GetActorTransform());
	fireTurretInstance->SetActorScale3D(FVector(1,1,1));
	fireTurretInstance->SetActorRotation(FQuat::Identity); 
	fireTurretInstance->SetActorEnableCollision(false);                                          
	fireTurretInstance->SetIsActive(false);

	waterTurretInstance = GetWorld()->SpawnActor<ATurret>(waterTurret, GetActorTransform());
	waterTurretInstance->SetActorScale3D(FVector(1,1,1));
	waterTurretInstance->SetActorRotation(FQuat::Identity); 
	waterTurretInstance->SetActorEnableCollision(false);                                          
	waterTurretInstance->SetIsActive(false);

	plantTurretInstance = GetWorld()->SpawnActor<ATurret>(plantTurret, GetActorTransform());
	plantTurretInstance->SetActorScale3D(FVector(1,1,1));
	plantTurretInstance->SetActorRotation(FQuat::Identity); 
	plantTurretInstance->SetActorEnableCollision(false);                                          
	plantTurretInstance->SetIsActive(false);

	FString floatToText = FString::SanitizeFloat(normalTurretInstance->GetBuyPrice());
	selectWidgetInstance->normalTurretBuyPrice->SetText(FText::FromString(floatToText));
	floatToText = FString::SanitizeFloat(fireTurretInstance->GetBuyPrice());
	selectWidgetInstance->fireTurretBuyPrice->SetText(FText::FromString(floatToText));
	floatToText = FString::SanitizeFloat(waterTurretInstance->GetBuyPrice());
	selectWidgetInstance->waterTurretBuyPrice->SetText(FText::FromString(floatToText));
	floatToText = FString::SanitizeFloat(plantTurretInstance->GetBuyPrice());
	selectWidgetInstance->plantTurretBuyPrice->SetText(FText::FromString(floatToText));
}

// Called every frame
void ACowPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (isPlacingTurret)
	{
		PlaceTurret();
		selectWidgetInstance->buttonsCanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		selectWidgetInstance->buttonsCanvasPanel->SetVisibility(ESlateVisibility::Visible);
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

	InputComponent->BindAxis("Horizontal", this, &ACowPlayer::MoveHorizontal);
	InputComponent->BindAxis("Vertical", this, &ACowPlayer::MoveVertical);
	InputComponent->BindAxis("HorizontalRotation", this, &ACowPlayer::RotateHorizontal);
	
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ACowPlayer::SpawnTurret);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ACowPlayer::SelectTurret);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &ACowPlayer::ExitPlaceTurret);
}

void ACowPlayer::MoveHorizontal(float horizontalMovement)
{
	AddActorLocalOffset(FVector::RightVector * horizontalMovement * camSpeed);
}

void ACowPlayer::MoveVertical(float verticalMovement)
{
	AddActorLocalOffset(FVector::ForwardVector * verticalMovement * camSpeed);
}

void ACowPlayer::RotateHorizontal(float horizontalRot)
{
	AddActorLocalRotation(FRotator(0.0f, horizontalRot * speedRot, 0.0f));
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
	
	const FCollisionQueryParams traceParams;
	GetWorld()->LineTraceSingleByChannel(hit, playerLocation, worldDirection, ECC_Visibility, traceParams);

	const FVector turretRaycastDirection;

	FHitResult turretHit;
	
	switch (turretElement)
	{
	case 0:
		normalTurretInstance->SetActorHiddenInGame(false);
		normalTurretInstance->SetActorLocation(hit.Location);
		
		GetWorld()->SweepSingleByChannel(turretHit,normalTurretInstance->GetActorLocation(),turretRaycastDirection, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(175.f), traceParams);
		if (turretHit.GetActor()->GetActorLocation().Z == 210.f)
		{
			if (gameStats->GetMilk() >= normalTurretInstance->GetBuyPrice())
			{
				canPlaceTurret = true;
			}
		}
		else
		{
			canPlaceTurret = false;
		}

		UE_LOG(LogTemp, Warning, TEXT("Objeto seleccionado: %s"), *turretHit.GetActor()->GetName());
		
		break;

	case 1:
		fireTurretInstance->SetActorHiddenInGame(false);
		fireTurretInstance->SetActorLocation(hit.Location);

		GetWorld()->SweepSingleByChannel(turretHit,fireTurretInstance->GetActorLocation(),turretRaycastDirection, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(175.f), traceParams);
		if (turretHit.GetActor()->GetActorLocation().Z == 210.f)
		{
			if (gameStats->GetMilk() >= fireTurretInstance->GetBuyPrice())
			{
				canPlaceTurret = true;
			}
		}
		else
		{
			canPlaceTurret = false;
		}
		break;
		
	case 2:
		waterTurretInstance->SetActorHiddenInGame(false);
		waterTurretInstance->SetActorLocation(hit.Location);

		GetWorld()->SweepSingleByChannel(turretHit,waterTurretInstance->GetActorLocation(),turretRaycastDirection, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(175.f), traceParams);
		if (turretHit.GetActor()->GetActorLocation().Z == 210.f)
		{
			if (gameStats->GetMilk() >= waterTurretInstance->GetBuyPrice())
			{
				canPlaceTurret = true;
			}
		}
		else
		{
			canPlaceTurret = false;
		}
		break;

	case 3:
		plantTurretInstance->SetActorHiddenInGame(false);
		plantTurretInstance->SetActorLocation(hit.Location);

		GetWorld()->SweepSingleByChannel(turretHit,plantTurretInstance->GetActorLocation(),turretRaycastDirection, FQuat(), ECC_Visibility, FCollisionShape::MakeSphere(175.f), traceParams);
		if (turretHit.GetActor()->GetActorLocation().Z == 210.f)
		{
			if (gameStats->GetMilk() >= plantTurretInstance->GetBuyPrice())
			{
				canPlaceTurret = true;
			}
		}
		else
		{
			canPlaceTurret = false;
		}
		break;
		
	}
	
	
}

void ACowPlayer::SpawnTurret()
{
	if (!isPlacingTurret || !canPlaceTurret)
	{
		return;
	}
	
	FTransform tempTransform;
	tempTransform.SetLocation(hit.Location);
	tempTransform.SetRotation(FQuat(FRotator(0,0,0)));

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
			gameStats->SpendMoney(tempTurret->GetBuyPrice());
		}
		break;

	case 1:
		newItem = pool->SpawnActor(fireTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();
			gameStats->SpendMoney(tempTurret->GetBuyPrice());
		}
		break;

	case 2:
		newItem = pool->SpawnActor(waterTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();
			gameStats->SpendMoney(tempTurret->GetBuyPrice());
		}
		break;

	case 3:
		newItem = pool->SpawnActor(plantTurret, tempTransform.GetLocation(), FRotator(0, 0, 0));
		if (ATurret* tempTurret = Cast<ATurret>(newItem))
		{
			tempTurret->SetActorEnableCollision(true);
			tempTurret->ActivateCollision();
			gameStats->SpendMoney(tempTurret->GetBuyPrice());
		}
		break;
	}
	
	
	isPlacingTurret = false;
}

void ACowPlayer::SellTurret()
{
	gameStats->SpendMoney(-selectedTurret->GetSellPrice());
	selectedTurret->Despawn();
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
	
	const FCollisionQueryParams traceParams;
	GetWorld()->LineTraceSingleByChannel(hit, playerLocation, worldDirection, ECC_Visibility, traceParams);
	

	if (ATurret* turretSelected = Cast<ATurret>(hit.GetActor()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Objeto seleccionado: %s"), *turretSelected->GetName());
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

		switch (turretSelected->Element)
		{
		case 0:
			selectWidgetInstance->targetCowTypeText->SetText(FText::FromString("Normal Cow"));
			break;

		case 1:
			selectWidgetInstance->targetCowTypeText->SetText(FText::FromString("Fire Cow"));
			break;

		case 2:
			selectWidgetInstance->targetCowTypeText->SetText(FText::FromString("Water Cow"));
			break;

		case 3:
			selectWidgetInstance->targetCowTypeText->SetText(FText::FromString("Plant Cow"));
			break;
		}

		DrawDebugSphere(GetWorld(), turretSelected->GetActorLocation(), turretSelected->GetRange(), 64, FColor::Red, false, 3.f, 0, 8.f);
		
		FString floatToText = "Attack Power-> " + FString::SanitizeFloat(turretSelected->GetAttackPower());
		selectWidgetInstance->targetCowAttackText->SetText(FText::FromString(floatToText));
		
		floatToText = "Attack Velocity-> " + FString::SanitizeFloat(turretSelected->GetAttackVelocity());
		selectWidgetInstance->targetCowVelocityText->SetText(FText::FromString(floatToText));
		
		floatToText = "Attack Range-> " + FString::SanitizeFloat(turretSelected->GetRange());
		selectWidgetInstance->targetCowRangeText->SetText(FText::FromString(floatToText));
		
		selectWidgetInstance->targetCanvasPanel->SetVisibility(ESlateVisibility::Visible);
	}

}

