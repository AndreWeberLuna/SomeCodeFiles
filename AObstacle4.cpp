// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle4.h"
#include "ACMeshHit.h"

// Sets default values
AAObstacle4::AAObstacle4()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize actor components
	HitComp = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component for wall"));

	// Initialize components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = Base;
	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall mesh"));
	Wall->SetupAttachment(Base);

}

// Called when the game starts or when spawned
void AAObstacle4::BeginPlay()
{
	Super::BeginPlay();

	// Add the wall to hit
	HitComp->AddToHit(Wall);
}

// Called every frame
void AAObstacle4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

