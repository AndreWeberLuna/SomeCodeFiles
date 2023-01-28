// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle23.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle23 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle23();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root; // Root component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base1; // First rotating base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base2; // Second rotating base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base3; // Third rotating base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle1_1; // First obstacle for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle2_1; // Second obstacle for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle3_1; // Third obstacle for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle4_1; // Fourth obstacle for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle1_2; // First obstacle for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle2_2; // Second obstacle for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle3_2; // Third obstacle for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle1_3; // First obstacle for third base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle2_3; // Second obstacle for third base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ramp1; // Ramp for fist base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ramp2; // Ramp for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Machine1; // Mesh to convert obstacles for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Machine2; // Mesh to convert obstacles for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Machine3; // Mesh to convert obstacles for third base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* InitializeCollision; // Collision to initialize obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Base2Collision; // Collision to prevent player from jumping to second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Base3Collision; // Collision to prevent player from jumping to third base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* FinishBase1Collision; // Collision to determine the player passed first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* FinishBase2Collision; // Collision to determine the player passed second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* ChangeMesh1Collision; // Collision to change the obstacle mesh on first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* ChangeMesh2Collision; // Collision to change the obstacle mesh on second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* ChangeMesh3Collision; // Collision to change the obstacle mesh on third base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BlockCollision1; // First collision to prevent the player from cheating

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BlockCollision2; // Second collision to prevent the player from cheating

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComponent1; // Rotation component for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshRotation* RotationComponent2; // Rotation component for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshRotation* RotationComponent3; // Rotation component for third base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComponent; // Hit component for obstacles

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACSplinePath* SplineRoute1; // Spline for first base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACSplinePath* SplineRoute2; // Spline for second base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACSplinePath* SplineRoute3; // Spline for third base

	/* Designer parameters */



	/* Programmer variables */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPassedLevel1; // Has the player passed the first level

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPassedLevel2; // Has the player passed the second level

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanPassToLevel2; // Bool to determine if to disable level two collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanPassToLevel3; // Bool to determine if to disable level three collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef; // Reference to the local player

	// FUNCTIONS

	// Function to be called when initialize collision begin overlaps
	UFUNCTION()
	void OnInitializeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called when initialize collision end overlaps
	UFUNCTION()
	void OnInitializeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to be called when Base2Collision begin overlaps
	UFUNCTION()
	void OnBase2CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called when Base3Collision begin overlaps
	UFUNCTION()
	void OnBase3CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called when FinishBase1Collision begin overlaps
	UFUNCTION()
	void OnFinishBase1CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called when FinishBase2Collision begin overlaps
	UFUNCTION()
	void OnFinishBase2CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called when FinishBase1Collision end overlaps
	UFUNCTION()
	void OnFinishBase1CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to be called when FinishBase2Collision end overlaps
	UFUNCTION()
	void OnFinishBase2CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
