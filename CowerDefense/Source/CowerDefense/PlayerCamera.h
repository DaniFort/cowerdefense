// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCamera.generated.h"

class UCameraComponent;
class USphereComponent;
class USelectWidget;

UCLASS()
class COWERDEFENSE_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCamera();

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* firstPersonCamera = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* playerCollider = nullptr;
	
	UPROPERTY(EditAnywhere) TSubclassOf<USelectWidget> selectWidget;
	UPROPERTY() USelectWidget* selectWidgetInstance = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float horizontalMovement);
};
