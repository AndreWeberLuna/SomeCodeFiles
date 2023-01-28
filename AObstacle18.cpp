// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle18.h"
#include "Components/BoxComponent.h"
#include "ACOneCurveTimeline.h"
#include "Kismet/GameplayStatics.h"
#include "COBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAObstacle18::AAObstacle18()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor mesh"));
	Floor->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision for to trigger events"));
	BoxCollision->SetupAttachment(Floor);

	// Initialize function components
	TimelineComponent = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to rotate the floor"));

	// Initialize variable
	RotationTarget = FRotator(0.f, 0.f, 15.f);
	LowGroundFriction = 0.f;

}

// Called when the game starts or when spawned
void AAObstacle18::BeginPlay()
{
	Super::BeginPlay();

	// Bind functions to timeline
	TimelineComponent->OnTimelineTickDel.AddUObject(this, &AAObstacle18::OnTick);

	// Bind functions on begin and end overlap collision
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle18::OnBoxBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle18::OnBoxEndOverlap);

	// Get Player Reference
	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Initialize variables
	NegRotationTarget = FRotator(-RotationTarget.Pitch, -RotationTarget.Yaw, -RotationTarget.Roll);
	
}

// Called every frame
void AAObstacle18::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called on timeline tick
void AAObstacle18::OnTick(float Value)
{
	if(Value >= 0)
	{
		FRotator NewRotation = UKismetMathLibrary::RLerp(FRotator(0.f), RotationTarget, Value, true);
		Floor->SetRelativeRotation(NewRotation);
	}
	else
	{
		FRotator NewRotation = UKismetMathLibrary::RLerp(FRotator(0.f), NegRotationTarget, FMath::Abs(Value), true);
		Floor->SetRelativeRotation(NewRotation);
	}
}

// Function to be called on Box begin overlap
void AAObstacle18::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Stop the player from jumping and set lower ground friction
	PlayerRef->CC_SetJump(false);
	PlayerRef->GetCharacterMovement()->GroundFriction = LowGroundFriction;
}

// Function to be called on Box end overlap
void AAObstacle18::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Enable the player to jump and reset ground friction
	PlayerRef->CC_SetJump(true);
	PlayerRef->GetCharacterMovement()->GroundFriction = 13.f;
}
