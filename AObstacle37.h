// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle37.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle37 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle37();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root; // Root component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TargetWall; // Wall containing targets

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseFloor; // Mesh to respawn in

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Target1; // Target 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Target2; // Target 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Target3; // Target 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Target4; // Target 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Target5; // Target 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Target6; // Target 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UChildActorComponent* Swing; // Swing actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BlockCollision; // Collision to prevent player from passing

	/* Function Components */



	/* Designer parameters */

	// How many targets to hit in order to pass the obstacle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetNum;

	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetHits; // Number of targets that have been hit

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef; // Reference to local player

	// FUNCTIONS

	// Function to be called on Target hit
	UFUNCTION()
	void OnTargetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function to be called on Wall hit
	UFUNCTION()
	void OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
