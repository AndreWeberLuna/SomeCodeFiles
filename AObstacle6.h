// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle6.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle6 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle6();

	// VARIABLES

	/* Components */ 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base;

	/* Actor components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
