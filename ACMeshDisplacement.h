// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACMeshDisplacement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUMPLINGDUELS_API UACMeshDisplacement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACMeshDisplacement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Components

	UPROPERTY()
	USceneComponent* HandlingMesh; // Mesh to apply transform interpolation

	UPROPERTY(EditAnywhere, Category = "Timeline Curve")
	class UCurveFloat* CurveFloat; // The curve to be updated by the timeline

	UPROPERTY()
	class UTimelineComponent* Timeline; // Timeline to handle mesh's movement

	/* Designer Parameters */

	// Initial transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	FVector InitialLocation;

	// Final transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	FVector FinalLocation;

	// Should the timeline loop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	bool bLoop; 

	// Should it move on start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	bool bAutoPlay; 

	// How long should the movement last
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float Duration; 

	// Should the mesh move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float bActivated; 

	// FUNCTIONS

	// Function to call on timeline tick
	UFUNCTION()
	void TimelineTick(float CurveValue);

	// Function to set the handling mesh
	UFUNCTION()
	void SetHandlingMesh(USceneComponent* Mesh);

	// Function to stop moving
	UFUNCTION(BlueprintCallable)
	void StopMoving();
};
