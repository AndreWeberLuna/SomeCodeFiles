// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle35.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle35 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle35();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Wall; // Wall containing the obstacles

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross1; // Cross 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross2; // Cross 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross3; // Cross 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross4; // Cross 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross5; // Cross 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross6; // Cross 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross7; // Cross 7

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross8; // Cross 8

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross9; // Cross 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cross10; // Cross 10

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear1; // Rotating gear 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear2; // Rotating gear 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear3; // Rotating gear 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear4; // Rotating gear 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear5; // Rotating gear 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear6; // Rotating gear 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear7; // Rotating gear 7

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear8; // Rotating gear 8

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear9; // Rotating gear 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Gear10; // Rotating gear 10

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder1; // Cylinder 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder2; // Cylinder 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder3; // Cylinder 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder4; // Cylinder 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder5; // Cylinder 5

	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshRotation* RotationComponent; // Component to rotate crosses and gears

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshHit* HitComp; // Component to hit with gears and cylinders

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACMeshDisplacement* Cross1Displacement; // Component to move cross 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross2Displacement; // Component to move cross 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross3Displacement; // Component to move cross 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross4Displacement; // Component to move cross 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross5Displacement; // Component to move cross 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross6Displacement; // Component to move cross 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross7Displacement; // Component to move cross 7

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross8Displacement; // Component to move cross 8

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross9Displacement; // Component to move cross 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cross10Displacement; // Component to move cross 10

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cylinder1Displacement; // Component to move cylinder 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cylinder2Displacement; // Component to move cylinder 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cylinder3Displacement; // Component to move cylinder 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cylinder4Displacement; // Component to move cylinder 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACMeshDisplacement* Cylinder5Displacement; // Component to move cylinder 5

	/* Designer variables */



	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef; // Reference to local player

	// FUNCTIONS
	
	// Function to be called on cross hit
	UFUNCTION()
	void OnCrossHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
