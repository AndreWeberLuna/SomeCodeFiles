// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle8V2.h"
#include "Components/CapsuleComponent.h"
#include "COBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ACMeshRotation.h"

// Class constructor
AAObstacle8V2::AAObstacle8V2()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // Initialize components
    Fan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fan's mesh"));
    Fan->SetupAttachment(RootComponent);

    FanCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Fan collision"));
    FanCapsule->SetupAttachment(RootComponent);
    FanCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle8V2::OnBeginFanCapsuleOverlap);
    FanCapsule->OnComponentEndOverlap.AddDynamic(this, &AAObstacle8V2::OnEndFanCapsuleOverlap);

    FanRotationComp = CreateDefaultSubobject<UACMeshRotation>(TEXT("Fan rotation component"));

    // Initialize variables
    FanMaxForce = 15000000.f;
    FanMinForce = 9500000.f;
}

// Begin Play
void AAObstacle8V2::BeginPlay()
{
    Super::BeginPlay();

    FanRotationComp->AddToRotate(Fan);

}

// Function to work when the fan's capsule is overlapped
void AAObstacle8V2::OnBeginFanCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if(OtherActor != PlayerRef) // Check if the actor is our player
    {
        return;
    }

    // Start our timer to apply force
    FTimerDelegate AddForceTimerDel = FTimerDelegate::CreateUObject(this, &AAObstacle8V2::ApplyForce);
    GetWorldTimerManager().SetTimer(AddForceTimerHandle, AddForceTimerDel, .05, true);
}

// Function to call to when the fan's capsule ends overlapping
void AAObstacle8V2::OnEndFanCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Clear our timer
    GetWorldTimerManager().ClearTimer(AddForceTimerHandle);
}

// Function to call while the player is inside the fan's capsule
void AAObstacle8V2::ApplyForce()
{
    // How far is the player from the fan
    float DistancePlayerFan = FVector::Dist(PlayerRef->GetActorLocation(), FanCapsule->GetComponentLocation());

    // Calculate force to be applied and apply it
    float ForceToApply = UKismetMathLibrary::MapRangeClamped(DistancePlayerFan, 0.f, 1000.f, FanMaxForce, FanMinForce);
    PlayerRef->GetCharacterMovement()->AddForce(FVector(0.f, 0.f, ForceToApply));
}

