// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle22.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle22 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle22();

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
	UStaticMeshComponent* PotBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BoxBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* PotCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BlockCollision;

	

	/* Function components */



	/* Designer parameters */



	/* Programmer variables */



	// FUNCTIONS

};
