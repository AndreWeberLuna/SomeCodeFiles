// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle34.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle34 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle34();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform; // Root component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal1; // Petal mesh 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal2; // Petal mesh 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal3; // Petal mesh 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal4; // Petal mesh 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal5; // Petal mesh 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal6; // Petal mesh 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Petal7; // Petal mesh 7

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* InitialCollision; // Collision to start closing

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* InsideCollision;

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* OpenTl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComp;

	/* Designer Parameters */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float Aperture;

	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlayerInObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlayerInside;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTimelinePlay;

	// FUNCTIONS

	// Function to be called on OpenTl Tick
	UFUNCTION()
	void OnOpenTlTick(float Value);

	// Function to be called on OpenTl Finished
	UFUNCTION()
	void OnOpenTlFinished();

	// Function to be called on Initial collision begin overlap
	UFUNCTION()
	void OnInitialBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to be called on Initial collision end overlap
	UFUNCTION()
	void OnInitialEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to be called on Platform hit
	UFUNCTION()
	void OnPlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function to start closing the petals
	UFUNCTION()
	void StartClosing();

	// Function to be called when player is inside the flower
	UFUNCTION()	
	void OnInsideBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to be called when player leaves the inside of flower
	UFUNCTION()
	void OnInsideEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
