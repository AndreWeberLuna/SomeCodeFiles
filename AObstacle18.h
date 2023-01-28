// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle18.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle18 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle18();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root; // Root Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Floor; // Floor component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision; // To identify when the player enters and leaves the obstacle

	/* Function Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* TimelineComponent;

	/* Designer Parameters */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	FRotator RotationTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float LowGroundFriction;

	/* Programmer Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator NegRotationTarget;

	// FUNCTIONS

	// Function to be called on timeline tick
	UFUNCTION()
	void OnTick(float Value);

	// Function to be called on Box begin overlap
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called on Box end overlap
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
