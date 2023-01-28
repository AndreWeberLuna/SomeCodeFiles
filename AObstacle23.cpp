// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle23.h"
#include "ACMeshHit.h"
#include "ACMeshRotation.h"
#include "ACSplinePath.h"
#include "Components/CapsuleComponent.h"
#include "COBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AAObstacle23::AAObstacle23()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	Base1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First rotating base"));
	Base1->SetupAttachment(Root);

	Base2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second rotating base"));
	Base2->SetupAttachment(Root);

	Base3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third rotating base"));
	Base3->SetupAttachment(Root);

	Obstacle1_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First obstacle for first base"));
	Obstacle1_1->SetupAttachment(Root);

	Obstacle2_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second obstacle for first base"));
	Obstacle2_1->SetupAttachment(Root);

	Obstacle3_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third obstacle for first base"));
	Obstacle3_1->SetupAttachment(Root);

	Obstacle4_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fourth obstacle for first base"));
	Obstacle4_1->SetupAttachment(Root);

	Obstacle1_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First obstacle for second base"));
	Obstacle1_2->SetupAttachment(Root);

	Obstacle2_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second obstacle for second base"));
	Obstacle2_2->SetupAttachment(Root);

	Obstacle3_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third obstacle for second base"));
	Obstacle3_2->SetupAttachment(Root);

	Obstacle1_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First obstacle for third base"));
	Obstacle1_3->SetupAttachment(Root);

	Obstacle2_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second obstacle for third base"));
	Obstacle2_3->SetupAttachment(Root);

	Ramp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ramp for first base"));
	Ramp1->SetupAttachment(Root);

	Ramp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ramp for second base"));
	Ramp2->SetupAttachment(Root);

	Machine1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh to convert obstacles for first base"));
	Machine1->SetupAttachment(Root);

	Machine2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh to convert obstacles for second base"));
	Machine2->SetupAttachment(Root);

	Machine3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh to convert obstacles for third base"));
	Machine3->SetupAttachment(Root);

	SplineRoute1 = CreateDefaultSubobject<UACSplinePath>(TEXT("Spline for first base"));
	SplineRoute1->SetupAttachment(Root);

	SplineRoute2 = CreateDefaultSubobject<UACSplinePath>(TEXT("Spline for second base"));
	SplineRoute2->SetupAttachment(Root);

	SplineRoute3 = CreateDefaultSubobject<UACSplinePath>(TEXT("Spline for third base"));
	SplineRoute3->SetupAttachment(Root);

	InitializeCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to initialize obstacle"));
	InitializeCollision->SetupAttachment(Root);

	Base2Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to prevent player from jumping to second base"));
	Base2Collision->SetupAttachment(Root);

	Base3Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to prevent player from jumping to third base"));
	Base3Collision->SetupAttachment(Root);

	FinishBase1Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to determine the player passed first base"));
	FinishBase1Collision->SetupAttachment(Ramp1);

	FinishBase2Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to determine the player passed second base"));
	FinishBase2Collision->SetupAttachment(Ramp2);

	ChangeMesh1Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to change the obstacle mesh on first base"));
	ChangeMesh1Collision->SetupAttachment(Root);

	ChangeMesh2Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to change the obstacle mesh on second base"));
	ChangeMesh2Collision->SetupAttachment(Root);

	ChangeMesh3Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to change the obstacle mesh on third base"));
	ChangeMesh3Collision->SetupAttachment(Root);

	BlockCollision1 = CreateDefaultSubobject<UBoxComponent>(TEXT("First collision to prevent the player from cheating"));
	BlockCollision1->SetupAttachment(Machine1);

	BlockCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Second collision to prevent the player from cheating"));
	BlockCollision2->SetupAttachment(Machine2);

	// Initialize function components
	RotationComponent1 = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component for first base"));
	RotationComponent2 = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component for second base"));
	RotationComponent3 = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component for third base"));
	HitComponent = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component for obstacles"));

	// Set default values for variables
	bPassedLevel1 = false;
	bPassedLevel2 = false;
	bCanPassToLevel2 = false;
	bCanPassToLevel3 = false;

}

// Called when the game starts or when spawned
void AAObstacle23::BeginPlay()
{
	Super::BeginPlay();

	// Setup function components
	RotationComponent1->AddToRotate(Base1);
	RotationComponent2->AddToRotate(Base2);
	RotationComponent3->AddToRotate(Base3);
	HitComponent->AddToHit(Obstacle1_1);
	HitComponent->AddToHit(Obstacle2_1);
	HitComponent->AddToHit(Obstacle3_1);
	HitComponent->AddToHit(Obstacle4_1);
	HitComponent->AddToHit(Obstacle1_2);
	HitComponent->AddToHit(Obstacle2_2);
	HitComponent->AddToHit(Obstacle3_2);
	HitComponent->AddToHit(Obstacle1_3);
	HitComponent->AddToHit(Obstacle2_3);

	// Bind functions to events
	InitializeCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle23::OnInitializeBeginOverlap);
	InitializeCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle23::OnInitializeEndOverlap);
	Base2Collision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle23::OnBase2CollisionBeginOverlap);
	Base3Collision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle23::OnBase3CollisionBeginOverlap);
	FinishBase1Collision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle23::OnFinishBase1CollisionBeginOverlap);
	FinishBase1Collision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle23::OnFinishBase1CollisionEndOverlap);
	FinishBase2Collision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle23::OnFinishBase2CollisionBeginOverlap);
	FinishBase2Collision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle23::OnFinishBase2CollisionEndOverlap);
	
	// Get Player Reference
	PlayerRef = HitComponent->PlayerRef;
}

// Called every frame
void AAObstacle23::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called when initialize collision begin overlaps
void AAObstacle23::OnInitializeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

// Function to be called when initialize collision end overlaps
void AAObstacle23::OnInitializeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Reset passed levels
	bPassedLevel1 = false;
	bPassedLevel2 = false;
	bCanPassToLevel2 = false;
	bCanPassToLevel3 = false;
}

// Function to be called when Base2Collision begin overlaps
void AAObstacle23::OnBase2CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Check if overlapping actor is local player
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Check if local player is entering the second collision via the ramp
	if(!bPassedLevel1)
	{
		if(!bCanPassToLevel2)
		{
			PlayerRef->CC_Respawn();
		}
		else
		{
			bPassedLevel1 = true;
		}
	}

}

// Function to be called when Base3Collision begin overlaps
void AAObstacle23::OnBase3CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Check if overlapping actor is local player
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Check if local player is entering the second collision via the ramp
	if(!bPassedLevel2)
	{
		if(!bCanPassToLevel3)
		{
			PlayerRef->CC_Respawn();
		}
		else
		{
			bPassedLevel2 = true;
		}
	}
}

// Function to be called when FinishBase1Collision begin overlaps
void AAObstacle23::OnFinishBase1CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Check if overlapping actor is local player
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Enable player to pass to second level
	bCanPassToLevel2 = true;
}

// Function to be called when FinishBase2Collision begin overlaps
void AAObstacle23::OnFinishBase2CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Check if overlapping actor is local player
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Enable player to pass to third level
	bCanPassToLevel3 = true;
}

// Function to be called when FinishBase1Collision end overlaps
void AAObstacle23::OnFinishBase1CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if overlapping actor is local player
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Disable player to pass to second level
	bCanPassToLevel2 = false;
}

// Function to be called when FinishBase2Collision end overlaps
void AAObstacle23::OnFinishBase2CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if overlapping actor is local player
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Disable player to pass to third level
	bCanPassToLevel3 = false;
}
