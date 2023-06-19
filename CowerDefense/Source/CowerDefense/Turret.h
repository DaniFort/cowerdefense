// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CowerDefense/ObjectPooler/PooledObject.h"

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
enum class ElementTypes : uint8 {
	None = 0		UMETA(DisplayName = "None"),
	Fire = 1        UMETA(DisplayName = "Fire"),
	Water = 2       UMETA(DisplayName = "Water"),
	Plant = 3		UMETA(DisplayName = "Plant"),
};

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
		ElementTypes Element;
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

	void SetIsActive(bool bIsActive) { isActive = bIsActive; }
	
private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		bool isActive = false;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float attackPower;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float attackVelocity;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		int buyPrice;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		int sellPrice;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		float range;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
		USceneComponent* pivotStaticMesh;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess), BlueprintReadWrite)
		TArray<USceneComponent*> shootPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseEnemy*> enemiesDetected;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(CallInEditor)
		void ShootMilkBeam();
	
	UFUNCTION()
	void RotateTowardsEnemy(FVector whereToLook);
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Spawn()override;
	virtual void Despawn()override;


};
