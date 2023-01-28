// Fill out your copyright notice in the Description page of Project Settings.


#include "ACOneCurveTimeline.h"
#include "Components/TimelineComponent.h"

// Sets default values for this component's properties
UACOneCurveTimeline::UACOneCurveTimeline()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	// Create default values
	bLoop = true;
	bAutoPlay = true;
	Duration = 1.f;

}


// Called when the game starts
void UACOneCurveTimeline::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat FloatDel; // Float timeline delegate to be binded with TimelineTick(float CurveValue)
	FOnTimelineEvent OnFinishedDel; // On finished delegate to be binded with OnFinished()

	if(CurveFloat) // Check if CurveFloat is valid
	{
		FloatDel.BindUFunction(this, FName("TimelineTick")); // Bind TimelineTick to the delegate
		OnFinishedDel.BindUFunction(this, FName("OnFinished")); // Bind OnFinished to the delegate

		Timeline->AddInterpFloat(CurveFloat, FloatDel); // Run the function related to FloatDel and use CurveFloat as a parameter
		Timeline->SetLooping(bLoop); // Set Looping
		Timeline->SetPlayRate(1/Duration); // Set the speed of the timeline
		Timeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); // Use LastKeyFrame to determine the timeline's duration
		Timeline->SetTimelineFinishedFunc(OnFinishedDel); // Run the function related to OnFinishedDel

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
void UACOneCurveTimeline::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

// Function to run every tick when timeline is playing
void UACOneCurveTimeline::TimelineTick(float CurveValue)
{
	OnTimelineTickDel.Broadcast(CurveValue);
}


// Fired when the timeline is finished
void UACOneCurveTimeline::OnFinished()
{
	OnTimelineFinishedDel.Broadcast();
}

// Function to play timeline
void UACOneCurveTimeline::PlayTimeline()
{
	Timeline->Play();
}

// Function to play timeline from start
void UACOneCurveTimeline::PlayTimelineFromStart()
{
	Timeline->PlayFromStart();
}

// Function to stop the timeline
void UACOneCurveTimeline::StopTimeline()
{
	Timeline->Stop();
}

// Function to reverse the timeline
void UACOneCurveTimeline::ReverseTimeline()
{
	Timeline->Reverse();
}
