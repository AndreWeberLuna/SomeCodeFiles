// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACOneCurveTimeline.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTimelineFinished)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimelineTick, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUMPLINGDUELS_API UACOneCurveTimeline : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACOneCurveTimeline();


	// VARIABLES

	UPROPERTY()
	class UTimelineComponent* Timeline; // Component's timeline

	UPROPERTY(EditAnywhere, Category = "Timeline Curve")
	class UCurveFloat* CurveFloat; // The curve to be updated by the timeline

	FOnTimelineFinished OnTimelineFinishedDel; // Delegate to be called when the timeline is finished
	FOnTimelineTick OnTimelineTickDel; // Delegate to be called when the timeline ticks

	/* Designer Parameters */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	bool bLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	bool bAutoPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float Duration;


	// FUNCTIONS

	// Function run every frame when timeline is playing
	UFUNCTION()
	void TimelineTick(float CurveValue);

	// Fired when the timeline is finished
	UFUNCTION()
	void OnFinished();

	// Function to play timeline
	UFUNCTION()
	void PlayTimeline();

	// Function to play timeline from start
	UFUNCTION()
	void PlayTimelineFromStart();

	// Function to stop the timeline
	UFUNCTION()
	void StopTimeline();

	// Function to reverse the timeline
	UFUNCTION()
	void ReverseTimeline();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
