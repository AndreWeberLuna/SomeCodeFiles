// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle13V1.h"
#include "ACOneCurveTimeline.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TimelineComponent.h"

AAObstacle13V1::AAObstacle13V1()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // Initialize function components
    Ring1Timeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline for the first ring"));
    Ring2Timeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline for the second ring"));

    // Initialize variables
    Ring1MaxSize = 10.f;
    Ring2MaxSize = 10.f;
    ParticleMinSize = .5f;
    ParticleMaxSize = 7.f;
    MinParticleNum = 1.f;
    MaxParticleNum = 3.f;
}

void AAObstacle13V1::BeginPlay()
{
    Super::BeginPlay();

    // Bind functions to the timeline
    Ring1Timeline->OnTimelineTickDel.AddUObject(this, &AAObstacle13V1::OnRing1TlTick);
    Ring2Timeline->OnTimelineTickDel.AddUObject(this, &AAObstacle13V1::OnRing2TlTick);

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AAObstacle13V1::ActivateSecondRing, .01f, false, Ring1Timeline->Duration/2);
}

// Function to work on ring1timeline tick
void AAObstacle13V1::OnRing1TlTick(float Value)
{
    // Set scale
    float Scale = (Value * Ring1MaxSize) + 1;
    Ring1->SetRelativeScale3D(FVector(Scale, Scale, 1));

    // Set particle scale
    if(FirstNiagara)
    {
        float ParticleScale = UKismetMathLibrary::MapRangeClamped(Value, 0.f, 1.f, ParticleMinSize, ParticleMaxSize);
        FirstNiagara->SetFloatParameter(FName("ParticleScale"), ParticleScale);
    }

    // Check if we should stop spawning
    bool bSpawn = Ring1Timeline->Duration - 1.5f >= (Ring1Timeline->Timeline->GetPlaybackPosition()) * Ring1Timeline->Duration;
    if(bSpawn)
    {
        // Set spawn rate depeding on scale
        int32 ParticleNum = FMath::Floor(UKismetMathLibrary::MapRangeClamped(Value * 1000.f, 0, 1000.f, MinParticleNum, MaxParticleNum));
        FirstNiagara->SetIntParameter(FName("ParticleNum"), ParticleNum);
    }
    else
    {
        FirstNiagara->SetIntParameter(FName("ParticleNum"), 0);
    }
}

// Function to work on ring1timeline tick
void AAObstacle13V1::OnRing2TlTick(float Value)
{
    // Set scale
    float Scale = (Value * Ring2MaxSize) + 1;
    Ring2->SetRelativeScale3D(FVector(Scale, Scale, 1));

    // Set particle scale
    if(SecondNiagara)
    {
        float ParticleScale = UKismetMathLibrary::MapRangeClamped(Value, 0.f, 1.f, ParticleMinSize, ParticleMaxSize);
        SecondNiagara->SetFloatParameter(FName("ParticleScale"), ParticleScale);
    }

    // Check if we should stop spawning
    bool bSpawn = Ring2Timeline->Duration - 1.5f >= (Ring2Timeline->Timeline->GetPlaybackPosition()) * Ring2Timeline->Duration;
    if(bSpawn)
    {
        // Set spawn rate depending on scale
        int32 ParticleNum = FMath::Floor(UKismetMathLibrary::MapRangeClamped(Value * 1000.f, 0, 1000.f, MinParticleNum, MaxParticleNum));
        SecondNiagara->SetIntParameter(FName("ParticleNum"), ParticleNum);
    }
    else
    {
        SecondNiagara->SetIntParameter(FName("ParticleNum"), 0);
    }
}

// Function to activate the second ring
void AAObstacle13V1::ActivateSecondRing()
{
    if(Ring2Timeline)
    {
        Ring2Timeline->Timeline->PlayFromStart();
    }
    
}
