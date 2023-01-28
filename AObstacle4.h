// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle4.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle4 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle4();

	// VARIABLES

	/* Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base; // Base floor mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall; // Hitting wall

	/* Actor components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComp; // Hit component

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
