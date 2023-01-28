// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle20.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle20 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle20();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Rail1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Rail2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* InitializeCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* Spline1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HammerBase1_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HammerBase1_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HammerBase2_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HammerBase2_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Hammer1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Hammer2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* HitCollision1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* HitCollision2;
	

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Hammer1MovementTl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* Hammer2MovementTl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* Swing1Tl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* Swing2Tl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* RecoveryTl;

	/* Designer parameters */



	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWorking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanSwing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Hammer1LastPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Hammer2LastPos;

	// FUNCTIONS

	// Function to trigger on hammer hit
	UFUNCTION()
	void OnHammerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	// Function to trigger on first hammer 
	UFUNCTION()
	void OnFirstCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to trigger on second hammer 
	UFUNCTION()
	void OnSecondCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called on hammer1movement tick
	UFUNCTION()
	void OnMovement1Tick(float Value);

	// Function to be called on hammer2movement tick
	UFUNCTION()
	void OnMovement2Tick(float Value);

	// Function to be called on swing1 tick
	UFUNCTION()
	void OnSwing1Tick(float Value);

	// Function to be called on swing1 finished
	UFUNCTION()
	void OnSwing1Finished();

	// Function to be called on swing2 finished
	UFUNCTION()
	void OnSwing2Finished();

	// Function to be called on swing1 tick
	UFUNCTION()
	void OnSwing2Tick(float Value);

	// Function to be called on recovery tick
	UFUNCTION()
	void OnRecoveryTick(float Value);

	// Function to be called on initialize collision begin overlap
	UFUNCTION()
	void OnInitialBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to be called on initialize collision end overlap
	UFUNCTION()
	void OnInitialEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
