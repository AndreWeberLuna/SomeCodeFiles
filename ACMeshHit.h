// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACMeshHit.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUMPLINGDUELS_API UACMeshHit : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACMeshHit();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	TArray<UStaticMeshComponent*> HitMeshes; // What are the meshes we want to hit the player

	UPROPERTY(BlueprintReadWrite)
	class ACOBase* PlayerRef; // Our Player Reference

	UPROPERTY(BlueprintReadWrite)
	bool bActivated; // Is our mesh ready to hit again

	UPROPERTY()
	FTimerHandle ActivationTimerHandle; // Handle for our activation timer


	/* Designer Parameters */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MaxRotationForce; // How fast to rotate if Ragdoll

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	bool bRagdoll; // Should Ragdoll

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MinHorizontalHit; // Min Horizontal Hit Force

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MaxHorizontalHit; // Max Horizontal Hit Force

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float VerticalHitForce; // Parameter of Vertical Hit Force

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Designer Parameters")
	float MinVerticalForce; // Parameter of minimum Hit Force



	// FUNCTIONS

	// Get Rotation Value
	float GetRotation(FVector HitLocation, UPrimitiveComponent* HitComponent);

	// Get Impulse Value
	FVector GetImpulse(FVector HitNormal);

	// Add Mesh to Hitting meshes list
	void AddToHit(UStaticMeshComponent* Mesh);

	// If it hits my player Calculate Hit Force and HitRotation if Ragdoll is activated, send the info to the player to apply the hit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function called to reactivate our hit property
	UFUNCTION()
	void ActivateHit();


};
