// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AObstacle8.h"
#include "AObstacle8V2.generated.h"

/**
 * 
 */
UCLASS()
class DUMPLINGDUELS_API AAObstacle8V2 : public AAObstacle8
{
	GENERATED_BODY()
	
public:

	// Class' constructor
	AAObstacle8V2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle AddForceTimerHandle; // Timer handle for when the player is over the fan

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float FanMinForce; // Timer handle for when the player is over the fan

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float FanMaxForce; // Timer handle for when the player is over the fan

	// COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fan; // Mesh's fan

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* FanCapsule; // Mesh's fan

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* FanRotationComp; // Rotation component for the fan

	//FUNCTIONS
	
	// Function to work when the fan's capsule is overlapped
	UFUNCTION()
	void OnBeginFanCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to call to when the fan's capsule ends overlapping
	UFUNCTION()
	void OnEndFanCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to call while the player is inside the fan's capsule
	UFUNCTION()
	void ApplyForce();


};
