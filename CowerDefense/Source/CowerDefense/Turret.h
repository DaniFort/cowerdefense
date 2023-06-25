// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CowProperties.h"
#include "CowerDefense/ObjectPooler/PooledObject.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class USphereComponent;
class ABaseEnemy;
class UNiagaraComponent;

UENUM(NotBlueprintType)
enum class TargetType : uint8 {
	First = 0		UMETA(DisplayName = "Attack First"),
	Last = 1        UMETA(DisplayName = "Attack Last"),
	Fire = 2		UMETA(DisplayName = "Attack Fire"),
	Water = 3       UMETA(DisplayName = "Attack Water"),
	Plant = 4		UMETA(DisplayName = "Attack Plant"),
};

UCLASS()
class COWERDEFENSE_API ATurret : public AActor, public IPooledObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* staticMeshTurret = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* staticMeshBase = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* staticMeshStick = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* boxCollider = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* sphereCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EElements Element;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TargetType Target;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USceneComponent* shootPoint0 = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USceneComponent* shootPoint1 = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USceneComponent* shootPoint2 = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USceneComponent* shootPoint3 = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UNiagaraComponent* milkBeam;

	float GetAttackPower() { return attackPower; }
	float GetAttackVelocity() { return attackVelocity; }
	float GetRange() { return maxRange; }
	float GetBuyPrice() { return buyPrice; }
	float GetSellPrice() { return sellPrice; }
	
	
	void SetIsActive(bool bIsActive) { isActive = bIsActive; }

	void ActivateCollision();
	
private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		bool isActive = false;
	UPROPERTY(VisibleAnywhere)
		bool isEnablingCollision = false;
	UPROPERTY()
		float alphaCollision = 0; 
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float attackPower;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float attackVelocity;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess))
		float timeToAttack = 1.f;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess))
		float timeToAttackTotal = 1.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float winMultiplier = 1.5f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float loseMultiplier = 0.75f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float maxRange;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
		float range = 0;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		USceneComponent* pivotStaticMesh;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess), BlueprintReadWrite)
		TArray<USceneComponent*> shootPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseEnemy*> enemiesDetected;

	UPROPERTY(VisibleAnywhere)
	ABaseEnemy* enemyToAttack = nullptr;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		int buyPrice;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		int sellPrice;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(CallInEditor)
		void ShootMilkBeam();

	void SelectEnemyToAttack();
	
	UFUNCTION()
	void RotateTowardsEnemy();

	void EnableCollision();

	void AttackEnemy();
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Spawn()override;
	virtual void Despawn()override;

};
