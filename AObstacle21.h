// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle21.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle21 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle21();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cone1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cone2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cone3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cone4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cone5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cone6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallBase1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallRope1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ball1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallBase2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BallRope2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ball2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* EntranceCollision;

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* ConeHitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshHit* BallHitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* BallMovement1Tl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* BallMovement2Tl;

	/* Designer parameters */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundFriction;

	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef;

	// FUNCTIONS

	// Function to be called on ball movement 1 timeline
	UFUNCTION()
	void OnBallMovement1Tick(float Value);

	// Function to be called on ball movement 2 timeline
	UFUNCTION()
	void OnBallMovement2Tick(float Value);

	// Function to trigger on collision entrance
	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to trigger on collision end overlap
	UFUNCTION()
	void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
