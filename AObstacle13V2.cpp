// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle13V2.h"
#include "Components/TimelineComponent.h"
#include "ACOneCurveTimeline.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AAObstacle13V2::AAObstacle13V2()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // Initialize function components
    Ring1Timeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move the first ring"));
    Ring2Timeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move the second ring"));

    // Initialize variables
    Ring1Size = 15.f;
    Ring2Size = 15.f;
    ParticleSize = 7.f;
    ParticleNum = 3.f;
    RingXMovement = 500.f;
    RingYMovement = 500.f;

}

void AAObstacle13V2::BeginPlay()
{
    Super::BeginPlay();

    // Bind functions to timelines
    Ring1Timeline->OnTimelineTickDel.AddUObject(this, &AAObstacle13V2::OnRing1TlTick);
    Ring2Timeline->OnTimelineTickDel.AddUObject(this, &AAObstacle13V2::OnRing2TlTick);

    // Set the second timeline offset
    Ring2Timeline->Timeline->SetNewTime(.5);

    // Apply some designer parameters
    Ring1->SetRelativeScale3D(FVector(Ring1Size, Ring1Size, 0.f));
    Ring2->SetRelativeScale3D(FVector(Ring2Size, Ring2Size, 0.f));

    FirstNiagara->SetFloatParameter(FName("ParticleScale"), ParticleSize);
    FirstNiagara->SetFloatParameter(FName("ParticleNum"), ParticleNum);

    SecondNiagara->SetFloatParameter(FName("ParticleScale"), ParticleSize);
    SecondNiagara->SetFloatParameter(FName("ParticleNum"), ParticleNum);
}

// Function to work on ring1timeline tick
void AAObstacle13V2::OnRing1TlTick(float Value)
{
    // Get Y Relative Location
    float XLocation = Value * RingXMovement;

    // Get X Relative Location
    float YAxis = YAxisCurve->GetFloatValue(Ring1Timeline->Timeline->GetPlaybackPosition());
    float YLocation = YAxis * RingYMovement;

    // Set new relative location
    Ring1->SetRelativeLocation(FVector(XLocation, YLocation, 0.f), true);
}

// Function to work on ring2timeline tick
void AAObstacle13V2::OnRing2TlTick(float Value)
{
    // Get Y Relative Location
    float XLocation = Value * RingXMovement;

    // Get X Relative Location
    float YAxis = YAxisCurve->GetFloatValue(Ring2Timeline->Timeline->GetPlaybackPosition());
    float YLocation = YAxis * RingYMovement;

    // Set new relative location
    Ring2->SetRelativeLocation(FVector(XLocation, YLocation, 0.f), true);
}
