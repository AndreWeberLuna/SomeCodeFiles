// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AObstacle8.h"
#include "AObstacle8V1.generated.h"

/**
 * 
 */
UCLASS()
class DUMPLINGDUELS_API AAObstacle8V1 : public AAObstacle8
{
	GENERATED_BODY()
	
public:

	// Class' constructor
	AAObstacle8V1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// VARIABLES

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Trampoline; // Trampoline mesh to jump off of

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float TrampolineHitForce; // Force to launch the player with

	// FUNCTIONS

	// Function to fire on Trampoline player's Hit
	UFUNCTION()
	void OnTrampolineHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); 


};
