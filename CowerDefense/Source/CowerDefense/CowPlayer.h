// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CowPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#include "CowPlayer.generated.h"

class UCameraComponent;
class USphereComponent;
class USelectWidget;
class ATurret;

UCLASS()
class COWERDEFENSE_API ACowPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACowPlayer();

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* firstPersonCamera = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* playerCollider = nullptr;
	
	UPROPERTY(EditDefaultsOnly) TSubclassOf<USelectWidget> selectWidget;
	UPROPERTY() USelectWidget* selectWidgetInstance = nullptr;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<ATurret> normalTurret;
	UPROPERTY(BlueprintReadOnly) ATurret* normalTurretInstance = nullptr;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ATurret> fireTurret;
	UPROPERTY(BlueprintReadOnly) ATurret* fireTurretInstance = nullptr;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ATurret> waterTurret;
	UPROPERTY(BlueprintReadOnly) ATurret* waterTurretInstance = nullptr;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ATurret> plantTurret;
	UPROPERTY(BlueprintReadOnly) ATurret* plantTurretInstance = nullptr;

	virtual void SetIsPlacingTurret(bool bIsPlacing, EElements elementType);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
		bool isPlacingTurret = false;
	UPROPERTY(EditAnywhere)
		EElements turretElement;

	UPROPERTY(VisibleAnywhere)
	ACowPlayerController* cowPC = Cast<ACowPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	FHitResult hit;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float horizontalMovement);
	void PlaceTurret();
	void SpawnTurret();
	void ExitPlaceTurret();
};
