// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle12.generated.h"

UCLASS()
class DUMPLINGDUELS_API AAObstacle12 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAObstacle12();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// VARIABLES

	/* Scene Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root; // The root component

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform1; // Platform number 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform2; // Platform number 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform3; // Platform number 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform4; // Platform number 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform5; // Platform number 5

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform6; // Platform number 6

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform7; // Platform number 7

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform8; // Platform number 8

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Platform9; // Platform number 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Button; // Platform number 9

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* EntranceCollision; // Entrance collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ExitCollision; // Exit collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* FloorCollision; // Floor collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* FloorCollision2; // Second floor collision

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* ButtonCollision; // Button collision

	/* Function Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* ButtonTimeline; // Timeline to be used for the button

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UACOneCurveTimeline* ShowBlockTimeline; // Timeline to show the block order

	/* Designer Variables */

	// How many blocks to memorize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	int32 BlockNum;

	/* Programmer Variables */

	// Array containig the blocks
	UPROPERTY()
	TArray<UActorComponent*> BlockArray;

	// Player Reference
	UPROPERTY()
	class ACOBase* PlayerRef;

	// Is the obstacle completed
	UPROPERTY()
	bool bCompleted;

	// Is the obstacle working
	UPROPERTY()
	bool bWorking;

	// Is the obstacle working
	UPROPERTY()
	bool bEnabledBlock1;

	// Is the obstacle working
	UPROPERTY()
	bool bEnabledBlock2;

	// If the button is pressed
	UPROPERTY()
	bool bPressed;

	// Integer representing the position where the block collision should be
	UPROPERTY()
	int32 BlockCount;

	// Integer representing the position where the second block collision should be
	UPROPERTY()
	int32 BlockCount2;

	// Integer to keep count on which position of the array to show
	UPROPERTY()
	int32 CountVar;

	UMaterialInterface* MaterialInstance;
	UMaterialInstanceDynamic* EmissiveMaterial;
	UMaterialInstanceDynamic* NonEmissiveMaterial;

	// FUNCTIONS

	// Function to handle the button timeline tick
	UFUNCTION()
	void OnButtonTlTick(float Value);

	// Function to handle the button timeline finished
	UFUNCTION()
	void OnButtonTlFinished();

	// Function to handle the show block timeline tick
	UFUNCTION()
	void OnBlockTlTick(float Value);

	// Function to handle the show block timeline finished
	UFUNCTION()
	void OnBlockTlFinished();

	// Function to shuffle an array
	UFUNCTION()
	void ShuffleArray(TArray<UActorComponent*>& Array);

	// Function to work when the button is overlapped
	UFUNCTION()
	void OnButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// Function to call when the button ended overlapping
	UFUNCTION()
	void OnEndButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function to call when the entrance collision is overlapped
	UFUNCTION()
	void OnEntranceOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to call when the first block's collision is overlapped
	UFUNCTION()
	void OnBlock1Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to call when the second block's collision is overlapped
	UFUNCTION()
	void OnBlock2Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Function to reset all the blocks
	UFUNCTION()
	void ResetBlocks();
	
	// Set all the blocks to a collision
	UFUNCTION()
	void SetBlocksCollision(FName CollisionName);

	// Prepare the blocks to start the obstacle
	UFUNCTION()
	void InitializeBlocks();

	// Show the player the order to step in
	UFUNCTION()
	void VisualizeOrder();

	// To handle the first collision while the player jumps from block to block
	UFUNCTION()
	void UpdateCollision1();

	// To handle the second collision while the player jumps from block to block
	UFUNCTION()
	void UpdateCollision2();

};
