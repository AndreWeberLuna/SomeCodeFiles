// Fill out your copyright notice in the Description page of Project Settings.


#include "ACMeshDisplacement.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UACMeshDisplacement::UACMeshDisplacement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Initialize components
	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	// Initialize variables
	bLoop = true;
	bAutoPlay = true;
	Duration = 1.f;

	InitialLocation = FVector(0.f);
	FinalLocation = FVector(0.f, 0.f, 100.f);
	bActivated = true;
}


// Called when the game starts
void UACMeshDisplacement::BeginPlay()
{
	Super::BeginPlay();

	// Setup the timeline

	FOnTimelineFloat FloatDel;

	if(CurveFloat) // Check if CurveFloat is valid
	{
		FloatDel.BindUFunction(this, FName("TimelineTick")); // Bind TimelineTick to the delegate

		Timeline->AddInterpFloat(CurveFloat, FloatDel); // Run the function related to FloatDel and use CurveFloat as a parameter
		Timeline->SetLooping(bLoop); // Set Looping
		Timeline->SetPlayRate(1/Duration); // Set the speed of the timeline
		Timeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); // Use LastKeyFrame to determine the timeline's duration

		if(bAutoPlay) // If bAutoPlay is false, pause the timeline
		{
			Timeline->PlayFromStart();
		}
		else
		{
			Timeline->Stop();
		}
	}
	
}

// Called every frame
void UACMeshDisplacement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Function to call on timeline tick
void UACMeshDisplacement::TimelineTick(float CurveValue)
{
	// Lerp between the initial and final transforms to move
	FVector NewLocation = UKismetMathLibrary::VLerp(InitialLocation, FinalLocation, CurveValue);
	
	// Apply new location to selected mesh
	if(HandlingMesh && bActivated)
	{
		HandlingMesh->SetRelativeLocation(NewLocation);
	}

}

// Function to set the handling mesh
void UACMeshDisplacement::SetHandlingMesh(USceneComponent* Mesh)
{
	HandlingMesh = Mesh;
}

// Function to stop moving
void UACMeshDisplacement::StopMoving()
{
	bActivated = false;
}
