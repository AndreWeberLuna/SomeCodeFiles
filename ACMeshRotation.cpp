// Fill out your copyright notice in the Description page of Project Settings.


#include "ACMeshRotation.h"

// Sets default values for this component's properties
UACMeshRotation::UACMeshRotation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// Initiliaze the variables
	RotationRate = FRotator(0.f, 60.f, 0.f);
	bActivated = true;

}


// Called when the game starts
void UACMeshRotation::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UACMeshRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bActivated) // Is the component activated
	{
		// Rotate every mesh in our RotatingMeshes considering the DeltaTime
		for (auto Mesh : RotatingMeshes)
		{
			Mesh->AddLocalRotation(RotationRate * DeltaTime);
		}
	}
}

void UACMeshRotation::AddToRotate(USceneComponent* Mesh)
{
	// Add mesh to be rotated
	RotatingMeshes.Add(Mesh);
}

