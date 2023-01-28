// Fill out your copyright notice in the Description page of Project Settings.

#include "ACMeshHit.h"
#include "COBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UACMeshHit::UACMeshHit()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Initialize internal values
	bActivated = true;

	//Initialize the designer parameters
	MaxRotationForce = 100;
	bRagdoll = false;
	MinHorizontalHit = 150;
	MaxHorizontalHit = 700;
	VerticalHitForce = 1500;
	MinVerticalForce = 0;

}

// Called when the game starts
void UACMeshHit::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

// Called every frame
void UACMeshHit::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// If it hits my player Calculate Hit Force and HitRotation if Ragdoll is activated, send the info to the player to apply the hit
void UACMeshHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if(PlayerRef == OtherActor && bActivated)
	{
		// We need to calculate our rotation and impulse forces
		FHitResult HitRef = Hit; // Our hit copy
		float RotationForce = GetRotation(HitRef.Location, HitComponent); // The calculation of the Hit Rotation
		FVector ImpulseForce = GetImpulse(HitRef.Normal); // The calculation of the Hit Impulse

		// Send the info to our player
		PlayerRef->CC_OnObstacleHit(ImpulseForce, RotationForce, bRagdoll, Hit.Location);

		// Deactivate for a fraction of time to avoid multiple hits
		bActivated = false;
		GetOwner()->GetWorldTimerManager().SetTimer(ActivationTimerHandle, this, &UACMeshHit::ActivateHit, 0.2);

	}

}

// Add Mesh to Hitting meshes list and link delegate
void UACMeshHit::AddToHit(UStaticMeshComponent* Mesh)
{
	HitMeshes.Add(Mesh);
	Mesh->OnComponentHit.AddDynamic(this, &UACMeshHit::OnHit);
}

// Get Rotation Value
float UACMeshHit::GetRotation(FVector HitLocation, UPrimitiveComponent* HitComponent)
{
	float ComponentLength; // Store our hitting component's length
	FVector Dummy; // Useless Variable
	UKismetSystemLibrary::GetComponentBounds(HitComponent, Dummy, Dummy, ComponentLength); // Get length

	float HitDistance = FVector::Dist(HitLocation, HitComponent->GetComponentLocation()); // Distance from the component's center
	float RotationForce = (HitDistance / ComponentLength) * MaxRotationForce; // Rotation speed depeding on hit distance

	return RotationForce;
}

// Get Impulse Value
FVector UACMeshHit::GetImpulse(FVector HitNormal)
{
	if(PlayerRef)
	{
		UCharacterMovementComponent* MovementRef = Cast<UCharacterMovementComponent>(PlayerRef->GetCharacterMovement()); // Player's Character Movement Component Reference
		float Velocity = MovementRef->GetLastUpdateVelocity().Size2D(); // Player's Current Speed
		float HitForce = UKismetMathLibrary::MapRangeClamped(Velocity, 0.f, 720.f, MinHorizontalHit, MaxHorizontalHit); // How hard the hit was based on player's velocity
		FVector Impulse = HitNormal.operator*(-HitForce); // Impulse to be applied to the character
		float VerticalForce = UKismetMathLibrary::MapRangeClamped(Velocity, 0.f, 720.f, 0, VerticalHitForce); // How hard the hit was in vertical terms

		// Apply our Minimum Vertical Value
		Impulse.Z = UKismetMathLibrary::GetMax2D(FVector2D(VerticalForce, MinVerticalForce));
		return Impulse;
	} 
	else
	{
		return FVector(0);
	}

}

// Function called to reactivate our hit property
void UACMeshHit::ActivateHit()
{
	bActivated = true; // Activate the hit property
	GetOwner()->GetWorldTimerManager().ClearTimer(ActivationTimerHandle); // Clear timer as we don't use it anymore
}



