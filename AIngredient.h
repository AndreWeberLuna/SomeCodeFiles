// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIngredient.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAIngredient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIngredient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Ingredient; // Ingredient mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComponent;  // Component to rotate the mesh while the ingredient isn't picked up

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshDisplacement* DisplacementComponent; // Component to move the mesh while the ingredient isn't picked up

	// Function to destroy ingredient
	UFUNCTION(BlueprintImplementableEvent)
	void CC_Destroy();



};
