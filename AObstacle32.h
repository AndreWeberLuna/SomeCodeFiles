// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle32.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle32 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle32();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Base; // Ring mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade1; // Blade 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade2; // Blade 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade3; // Blade 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade4; // Blade 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade5; // Blade 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade6; // Blade 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade7; // Blade 7

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade8; // Blade 8

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade9; // Blade 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade10; // Blade 10

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade11; // Blade 11

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Blade12; // Blade 12

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* OpenTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HittingComponent;

	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade1InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade2InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade3InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade4InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade5InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade6InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade7InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade8InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade9InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade10InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade11InitialYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blade12InitialYaw;

	/* Designer parameters */

	// How much are the blades going to open
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float HoleAperture;

	// FUNCTIONS

	// Function to be called when local player touches any blade
	UFUNCTION()
	void OnBladeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function to be called on OpenTimeline Tick
	UFUNCTION()
	void OnOpenTlTick(float Value);
};
