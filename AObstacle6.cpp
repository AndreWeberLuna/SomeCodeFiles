// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle6.h"
#include "ACMeshRotation.h"

// Sets default values
AAObstacle6::AAObstacle6()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize actor components
	RotationComp = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component"));

	// Initialize components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = Base;

}

// Called when the game starts or when spawned
void AAObstacle6::BeginPlay()
{
	Super::BeginPlay();

	// Add our mesh to rotate
	RotationComp->AddToRotate(Base);
	
}

// Called every frame
void AAObstacle6::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

