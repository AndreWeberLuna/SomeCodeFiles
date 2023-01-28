// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle38.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle38 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle38();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root; // Root component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BlockCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* EndCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Dispenser; // Mesh to spawn ingredients

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* IngredientSpawnCollision; // Place where ingredients will spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DispenserPlatform; // Platform on dispenser side

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FunnelPlatform; // Platform on funnel side

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Funnel1; // First funnel to receive ingredients

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Funnel2; // Second funnel to receive ingredients

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Funnel1Collision; // Collision to detect ingredients for funnel 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Funnel2Collision; // Collision to detect ingredients for funnel 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block1_1; // Block in row 1 and column 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block2_1; // Block in row 2 and column 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block3_1; // Block in row 3 and column 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block4_1; // Block in row 4 and column 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block5_1; // Block in row 5 and column 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block6_1; // Block in row 6 and column 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block1_2; // Block in row 1 and column 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block2_2; // Block in row 2 and column 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block3_2; // Block in row 3 and column 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block4_2; // Block in row 4 and column 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block5_2; // Block in row 5 and column 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block6_2; // Block in row 6 and column 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block1_3; // Block in row 1 and column 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block2_3; // Block in row 2 and column 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block3_3; // Block in row 3 and column 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block4_3; // Block in row 4 and column 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block5_3; // Block in row 5 and column 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block6_3; // Block in row 6 and column 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block1_4; // Block in row 1 and column 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block2_4; // Block in row 2 and column 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block3_4; // Block in row 3 and column 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block4_4; // Block in row 4 and column 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block5_4; // Block in row 5 and column 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block6_4; // Block in row 6 and column 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block1_5; // Block in row 1 and column 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block2_5; // Block in row 2 and column 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block3_5; // Block in row 3 and column 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block4_5; // Block in row 4 and column 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block5_5; // Block in row 5 and column 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Block6_5; // Block in row 6 and column 5

	// MISSING INGREDIENT CLASS

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ButtonPlatform; // Platform for the button

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Button; // Pushable button

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* ButtonCollision; // Collision to push the button


	/* Function components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* ButtonTl; // Timeline to press button

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UACOneCurveTimeline* ShowBlocksTl; // Timeline to show block path

	/* Designer Parameters */

	// Number of ingredients to dunk in order to pass the obstacle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	int32 NumIngredients;

	// Distance to press the button when standing on top of it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float ButtonPressDistance;

	// Material to use when the block has collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	UMaterialInterface* PassMaterial;

	// Material to use when the block doesn't have collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	UMaterialInterface* NoPassMaterial;

	// Ingredient class to be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	TSubclassOf<class AAIngredient> IngredientClassRef;


	/* Programmer variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACOBase* PlayerRef; // Reference to local player

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> BlockArray; // Array containing the blocks

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> bWalkableArray; // Array containing bool if block is walkable

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DunkedIngredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ButtonInitialLocation; // To save original button location

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AAIngredient* LastIngredient; // Last ingredient to be spawned

	// FUNCTIONS

	// Function to initialize arrays
	UFUNCTION()
	void InitializeArrays();

	// Function to be called when an object begins overlap with funnel collision
	UFUNCTION()
	void OnFunnelBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to show the path on Show Blocks tick
	UFUNCTION()
	void OnShowBlocksTick(float Value);

	// Function to press the button on button timeline tick
	UFUNCTION()
	void OnButtonTick(float Value);

	// Function to activate timelines on button collision begin overlap
	UFUNCTION()
	void OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to reverse timelines on button collision end overlap
	UFUNCTION()
	void OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to determine the block path
	UFUNCTION()
	void SetNewPath();

	// Function to spawn new ingredient into the machine to be picked up
	UFUNCTION(BlueprintCallable)
	void SpawnIngredient();
	
	// Function to be called on BlockCollision begin overlap to disable jump
	UFUNCTION()
	void OnBlockCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to be called on BlockCollision end overlap to enable jump
	UFUNCTION()
	void OnBlockCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
