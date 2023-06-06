// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"

#include "SelectWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlayerCamera::APlayerCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	firstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	firstPersonCamera->SetupAttachment(RootComponent);

	playerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	playerCollider->SetupAttachment(RootComponent);

	//selectWidget->CreateDefaultSubobject<USelectWidget>(TEXT("Select Widget"));
}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	selectWidget->AddToViewport(0);
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APlayerCamera::Move);
}

void APlayerCamera::Move(float horizontalMovement)
{
	if (horizontalMovement > 0.f)
	{
		
	UE_LOG(LogTemp, Log, TEXT("horizontal"));
	}
}

