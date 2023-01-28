// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle14.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle14 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle14();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base; // Root of the actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RotatingBase; // Scene to rotate obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall1; // Wall number one

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall2; // Wall number two

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall3; // Wall number three

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall4; // Wall number four

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall5; // Wall number five

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall6; // Wall number six

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall7; // Wall number seven

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall8; // Wall number eight

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall9; // Wall number nine

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall10; // Wall number ten

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall11; // Wall number eleven

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall12; // Wall number twelve

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* InitializeCollision; // Collision to initialize obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleCollision; // Collision to end obstacle

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComponent; // Component to rotate the walls

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComponent; // Component to hit with the walls

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Movement1; // Timeline to rotate the walls

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* Movement2; // Timeline to rotate the walls

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* Movement3; // Timeline to rotate the walls

	/* Designer parameters */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MinDisplacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MaxDisplacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MaxDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MinDuration;

	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCurveFloat* SecondCurve; // Curve to control wall movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height1_7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height4_10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height2_8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height5_11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height3_9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height6_12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWorking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHalfEvent1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHalfEvent2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHalfEvent3;


	// FUNCTIONS

	// Function to move the first set of walls with movement1
	UFUNCTION()
	void MoveFirstSet(float FirstValue);

	// Function to move the first set of walls with movement2
	UFUNCTION()
	void MoveSecondSet(float FirstValue);

	// Function to move the first set of walls with movement3
	UFUNCTION()
	void MoveThirdSet(float FirstValue);

	// Function to be called when the first timeline is finished
	UFUNCTION()
	void FinishedFirstSet();

	// Function to be called when the second timeline is finished
	UFUNCTION()
	void FinishedSecondSet();

	// Function to be called when the third timeline is finished
	UFUNCTION()
	void FinishedThirdSet();

	// Function to get a random integer
	UFUNCTION()
	float GetRandomInt();

	// Function to be called on initialize collision overlap
	UFUNCTION()
	void OnInitialCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called on capsule collision overlap
	UFUNCTION()
	void OnEndCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
