// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SplineComponent.h"
#include "Math/UnrealMathUtility.h"
#include "BaseEnemy.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UENUM(NotBlueprintType)
enum class ElementType : uint8 {
	None = 0		UMETA(DisplayName = "None"),
	Fire = 1        UMETA(DisplayName = "Fire"),
	Water = 2       UMETA(DisplayName = "Water"),
	Plant = 3		UMETA(DisplayName = "Plant"),
};

UCLASS()
class COWERDEFENSE_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float health;
	// Sets default values for this pawn's properties
	ABaseEnemy();

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* staticMeshEnemy = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* boxCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ElementType Element;

protected:
	UPROPERTY()
		USplineComponent* splinePath;
	UPROPERTY()
		float moveSpeed;
	UPROPERTY()
		float timeProgression;
	UPROPERTY()
		float timeToFinish;

	virtual void BeginPlay() override;
	void follow_path();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};