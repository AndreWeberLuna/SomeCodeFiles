// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle13.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle13 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle13();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Designer Parameters */



	/* Programmer Variables */



	/* Scene Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base; // Root containing the base

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ring1; // First Ring

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ring2; // Second ring

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* FirstNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* SecondNiagara;

	/* Function Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComponent;


	// FUNCTIONS

};
