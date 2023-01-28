// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle3.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle3 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle3();


	// VARIABLES

	/* Components */ 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base; // Obstacle's base mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HitMesh1; // First hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fruit1_1; // First fruit for the first hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fruit1_2; // Second fruit for the first hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HitMesh2; // Second hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fruit2_1; // First fruit for the second hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fruit2_2; // Second fruit for the second hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HitMesh3; // Third hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fruit3_1; // First fruit for the third hitting mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Fruit3_2; // Second fruit for the third hitting mesh

	/* Actor Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* Mesh13RotationComp; // Rotation component for the the first and third hitting meshes

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* Mesh2RotationComp; // Rotation component for the second hitting meshes

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* MeshHitComp; // Hit component for the hitting meshes

	/* Designer Parameters */

	

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
