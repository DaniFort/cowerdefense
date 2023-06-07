// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "CowerDefense/ObjectPooler/PooledObject.h"

#include "BaseEnemy.generated.h"


class USkeletalMeshComponent;
class ASplainMeshActor;
class UBoxComponent;
class USplineComponent;

UENUM(NotBlueprintType)
enum class ElementType : uint8 {
	None = 0		UMETA(DisplayName = "None"),
	Fire = 1        UMETA(DisplayName = "Fire"),
	Water = 2       UMETA(DisplayName = "Water"),
	Plant = 3		UMETA(DisplayName = "Plant"),
};

UCLASS()
class COWERDEFENSE_API ABaseEnemy : public APawn , public IPooledObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		float health;
	// Sets default values for this pawn's properties
	ABaseEnemy();

	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* skeletalMeshEnemy = nullptr;
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* root = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* boxCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ElementType Element;

protected:
	UPROPERTY(VisibleAnywhere)
		USplineComponent* splinePath;
	UPROPERTY(EditDefaultsOnly)
		float moveSpeed;
	UPROPERTY()
		float timeProgression;
	UPROPERTY()
		float timeToFinish;
	UPROPERTY()
		bool isAlive;

	virtual void BeginPlay() override;
	void follow_path();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSplinePath(USplineComponent* spline);

	void ReachEnd();
	//pool
	virtual void Spawn()override;
	virtual void Despawn()override;

};