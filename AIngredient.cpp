// Fill out your copyright notice in the Description page of Project Settings.


#include "AIngredient.h"
#include "ACMeshRotation.h"
#include "ACMeshDisplacement.h"

// Sets default values
AAIngredient::AAIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Ingredient = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ingredient mesh"));
	SetRootComponent(Ingredient);

	// Initialize function components
	RotationComponent = CreateDefaultSubobject<UACMeshRotation>(TEXT("Component to rotate the mesh while unheld"));
	DisplacementComponent = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move the mesh while unheld"));

}

// Called when the game starts or when spawned
void AAIngredient::BeginPlay()
{
	Super::BeginPlay();

	RotationComponent->AddToRotate(Ingredient);
	DisplacementComponent->SetHandlingMesh(Ingredient);
	
}

// Called every frame
void AAIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

