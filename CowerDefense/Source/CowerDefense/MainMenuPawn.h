// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainMenuPawn.generated.h"

class UMainMenu;
class UCameraComponent;

UCLASS()
class COWERDEFENSE_API AMainMenuPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainMenuPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<UMainMenu> mainMenuWidget;
	UPROPERTY() UMainMenu* mainMenuWidgetInstance = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* firstPersonCamera = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
