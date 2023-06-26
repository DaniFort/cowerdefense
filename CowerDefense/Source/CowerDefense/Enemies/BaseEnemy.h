// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "CowerDefense/ObjectPooler/PooledObject.h"
#include "../CowProperties.h"
#include "Kismet/ImportanceSamplingLibrary.h"

#include "BaseEnemy.generated.h"


class USkeletalMeshComponent;
class ASplainMeshActor;
class UBoxComponent;
class USplineComponent;
class UNiagaraComponent;


//UENUM(NotBlueprintType)
//enum class ElementType : uint8 {
//	None = 0		UMETA(DisplayName = "None"),
//	Fire = 1        UMETA(DisplayName = "Fire"),
//	Water = 2       UMETA(DisplayName = "Water"),
//	Plant = 3		UMETA(DisplayName = "Plant"),
//};

UCLASS()
class COWERDEFENSE_API ABaseEnemy : public APawn , public IPooledObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float maxHealth;
	UPROPERTY(VisibleAnywhere)
	float health;
	UPROPERTY(EditDefaultsOnly)
		float damageOnWin{ 30 };
	// Sets default values for this pawn's properties
	ABaseEnemy();

	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* skeletalMeshEnemy = nullptr;
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* root = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* boxCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EElements Element;

	UPROPERTY(EditAnywhere)
		TArray<UNiagaraComponent*> NiagaraComponents;
	float GetAlpha() const { return alpha;}

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
	UPROPERTY(VisibleAnywhere)
		float alpha;
	virtual void BeginPlay() override;
	void follow_path();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSplinePath(USplineComponent* spline);

	void ReachEnd();

	EElements GetElement() const { return Element; }
	void ReceiveDamage(float damage);
	//pool
	virtual void Spawn()override;
	virtual void Despawn()override;

};