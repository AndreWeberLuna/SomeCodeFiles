// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AObstacle13.h"
#include "AObstacle13V1.generated.h"

/**
 * 
 */
UCLASS()
class DUMPLINGDUELS_API AAObstacle13V1 : public AAObstacle13
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAObstacle13V1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public: 

	// VARIABLES

	/* Designer Parameters */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float Ring1MaxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float Ring2MaxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float ParticleMinSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float ParticleMaxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MinParticleNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MaxParticleNum;

	/* Programmer Variables */



	/* Scene Components */



	/* Function Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Ring1Timeline; // Timeline to scale the first ring

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Ring2Timeline; // Timeline to scale the first ring

	// FUNCTIONS

	// Function to work on ring1timeline tick
	UFUNCTION()
	void OnRing1TlTick(float Value);

	// Function to work on ring2timeline tick
	UFUNCTION()
	void OnRing2TlTick(float Value);

	// Function to activate the second ring
	UFUNCTION()
	void ActivateSecondRing();
	
};
