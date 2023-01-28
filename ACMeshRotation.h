// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACMeshRotation.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUMPLINGDUELS_API UACMeshRotation : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACMeshRotation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActivated; // Should the component be activated

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	FRotator RotationRate; // How much and how fast we want to rotate the meshes

	UPROPERTY(BlueprintReadWrite, Category = "Designer Parameters")
	TArray<USceneComponent*> RotatingMeshes; // What are the meshes to be rotated

	// To add meshes to the Array
	void AddToRotate(USceneComponent* Mesh);

};

