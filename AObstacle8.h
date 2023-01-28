// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle8.generated.h"

UENUM(BlueprintType)
enum class ENextObstacle : uint8
{
	ENO_Value1 UMETA(DisplayName="First"),
	ENO_Value2 UMETA(DisplayName="Second"),
	ENO_Value3 UMETA(DisplayName="Third")
};

UCLASS()
class DUMPLINGDUELS_API AAObstacle8 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle8();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base; // Root mesh that will be rotated

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle1; // First hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle2; // Second hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Obstacle3; // Third hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACSplinePath* SplineRoute; // Spline that obstacles will follow

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* StartCollision; // Collision to start the obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* DeathCollision; // Collision to determine when the player has lost

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* JumpMesh; // Mesh for the player to jump

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* CrouchMesh; // Mesh for the player to crouch

	/* Actor Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComp; // Rotation component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComp; // Hitting component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Obs1MovementTl; // Timeline to control the first obstacle movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Obs2MovementTl; // Timeline to control the second obstacle movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* Obs3MovementTl; // Timeline to control the third obstacle movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* RotationResetTl; // Timeline to control the third obstacle movement

	/* Programmer Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef; // Rotation component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Obs1Progress; // First obstacle position in reference to the spline

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Obs2Progress; // Second obstacle position in reference to the spline

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Obs3Progress; // Third obstacle position in reference to the spline

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SplineLength; // To know how long the spline is

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZOffset1; // The offset depending on the type of the first obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZOffset2; // The offset depending on the type of the second obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZOffset3; // The offset depending on the type of the third obstacle

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabledDeathCollision; // If leaving death collision should end in respawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabledObstacle; // Is the obstacle working

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator InitialRotation; // Initial rotation before the obstacle starts to rotate

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator LastRotation; // Initial rotation before the obstacle starts to rotate

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle RespawnTimerHandle; // Timer handle to restart the obstacle when player loses

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle SetPlayRateHandle; // Timer handle to change timeline's play rate

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENextObstacle NextObstacle; // Enum to know which obstacle to keep track of

	/* Designer Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float ObstacleSpeed; // How fast should obstacles be moving

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float ObstacleFrequency; // Distance between incoming obstacles

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters", meta=(ClampMax= 0.84))
	float StartProgress; // How close should the obstacles be on start

	// FUNCTIONS

	/* Timeline functions */

	// Used on Obs1MovementTl tick to move the first obstacle
	UFUNCTION()
	void MoveObs1(float Progress);

	// Used on Obs2MovementTl tick to move the first obstacle
	UFUNCTION()
	void MoveObs2(float Progress);

	// Used on Obs3MovementTl tick to move the first obstacle
	UFUNCTION()
	void MoveObs3(float Progress);

	// Used on RotationResetTl tick to move the first obstacle
	UFUNCTION()
	void SetRotation(float Alpha);

	// Used on RotationResetTl on finished to disable the obstacle
	UFUNCTION()
	void OnFinishedRotating();

	/* Programmer functions */

	// To start the obstacle when the start collision is overlap by our player
	UFUNCTION()
	void StartObstacle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Overload of stop obstacle for when the call isn't from an overlap event
	UFUNCTION()
	void StopObstacle();

	// To restart the obstacle when the player loses
	UFUNCTION()
	void RestartObstacle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to check if the current obstacle should be respawned
	UFUNCTION()
	void CheckRespawn();

	// Setup an obstacle when respawning
	UFUNCTION()
	void SetupObstacle(UTimelineComponent* TimelineRef, int32 ObsNumber, float PlayPosition, UStaticMeshComponent* Mesh);

	// Set the timeline's play rate
	UFUNCTION()
	void SetPlayRate(float PlayRate);

	// Set the timeline's to play
	UFUNCTION()
	void PlayTimelines();

};
