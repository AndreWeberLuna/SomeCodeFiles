// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle13.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "ACMeshHit.h"

// Sets default values
AAObstacle13::AAObstacle13()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root of the obstacle"));
	SetRootComponent(Base);

	Ring1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First expanding ring"));
	Ring1->SetupAttachment(Base);

	Ring2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second expanding ring"));
	Ring2->SetupAttachment(Base);

	FirstNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara for the first ring"));
	FirstNiagara->SetupAttachment(Ring1);

	SecondNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara for the second ring"));
	SecondNiagara->SetupAttachment(Ring2);

	// Initialize function components
	HitComponent = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component"));

}

// Called when the game starts or when spawned
void AAObstacle13::BeginPlay()
{
	Super::BeginPlay();

	// Add meshes to hit
	HitComponent->AddToHit(Ring1);
	HitComponent->AddToHit(Ring2);
	
}

// Called every frame
void AAObstacle13::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

