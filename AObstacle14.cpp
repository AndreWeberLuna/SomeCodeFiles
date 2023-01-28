// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle14.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "ACMeshRotation.h"
#include "ACMeshHit.h"
#include "ACOneCurveTimeline.h"
#include "COBase.h"
#include "Curves/CurveFloat.h"

// Sets default values
AAObstacle14::AAObstacle14()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Initialize scene components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root component"));
	SetRootComponent(Base);

	RotatingBase = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent to rotate the walls"));
	RotatingBase->SetupAttachment(Base);

	Wall1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number one"));
	Wall1->SetupAttachment(RotatingBase);

	Wall2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number two"));
	Wall2->SetupAttachment(RotatingBase);

	Wall3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number three"));
	Wall3->SetupAttachment(RotatingBase);

	Wall4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number four"));
	Wall4->SetupAttachment(RotatingBase);

	Wall5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number five"));
	Wall5->SetupAttachment(RotatingBase);

	Wall6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number six"));
	Wall6->SetupAttachment(RotatingBase);

	Wall7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number seven"));
	Wall7->SetupAttachment(RotatingBase);

	Wall8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number eight"));
	Wall8->SetupAttachment(RotatingBase);

	Wall9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number nine"));
	Wall9->SetupAttachment(RotatingBase);

	Wall10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number ten"));
	Wall10->SetupAttachment(RotatingBase);

	Wall11 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number eleven"));
	Wall11->SetupAttachment(RotatingBase);

	Wall12 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall number twelve"));
	Wall12->SetupAttachment(RotatingBase);

	InitializeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to start obstacle"));
	InitializeCollision->SetupAttachment(Base);

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to end obstacle"));
	CapsuleCollision->SetupAttachment(Base);

	// Initialize function components
	RotationComponent = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component"));
	HitComponent = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component"));
	Movement1 = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move wall 1 4 7 10"));
	Movement2 = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move wall 2 5 8 11"));
	Movement3 = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move wall 3 6 9 12"));

	// Initialize variables
	bWorking = false;
	bHalfEvent1 = false;
	bHalfEvent2 = false;
	bHalfEvent3 = false;
	MaxDisplacement = 700.f;
	MinDisplacement = 400.f;
	MaxDuration = 5.f;
	MinDuration = 3.f;

}

// Called when the game starts or when spawned
void AAObstacle14::BeginPlay()
{
	Super::BeginPlay();

	// Bind function to collision and end overlaps
	InitializeCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle14::OnInitialCollisionOverlap);
	CapsuleCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle14::OnEndCapsuleOverlap);

	// Bind functions to our timelines
	Movement1->OnTimelineTickDel.AddUObject(this, &AAObstacle14::MoveFirstSet);
	Movement1->OnTimelineFinishedDel.AddUObject(this, &AAObstacle14::FinishedFirstSet);
	Movement2->OnTimelineTickDel.AddUObject(this, &AAObstacle14::MoveSecondSet);
	Movement2->OnTimelineFinishedDel.AddUObject(this, &AAObstacle14::FinishedSecondSet);
	Movement3->OnTimelineTickDel.AddUObject(this, &AAObstacle14::MoveThirdSet);
	Movement3->OnTimelineFinishedDel.AddUObject(this, &AAObstacle14::FinishedThirdSet);

	// Initialize hit component
	HitComponent->AddToHit(Wall1);
	HitComponent->AddToHit(Wall2);
	HitComponent->AddToHit(Wall3);
	HitComponent->AddToHit(Wall4);
	HitComponent->AddToHit(Wall5);
	HitComponent->AddToHit(Wall6);
	HitComponent->AddToHit(Wall7);
	HitComponent->AddToHit(Wall8);
	HitComponent->AddToHit(Wall9);
	HitComponent->AddToHit(Wall10);
	HitComponent->AddToHit(Wall11);
	HitComponent->AddToHit(Wall12);

	// Initialize rotation component
	RotationComponent->AddToRotate(RotatingBase);

	// Set initial int values
	Height1_7 = GetRandomInt();
	Height4_10 = GetRandomInt();
	
}

// Called every frame
void AAObstacle14::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to move the first set of walls with movement1
void AAObstacle14::MoveFirstSet(float FirstValue)
{
	float TimelinePosition = Movement1->Timeline->GetPlaybackPosition();

	// Get the z locations to apply
	float ZLocation1 = Height1_7 * FirstValue;
	float ZLocation2 = Height4_10 * SecondCurve->GetFloatValue(TimelinePosition);

	// Set first wallset positions
	Wall1->SetRelativeLocation(FVector(0.f, 0.f, ZLocation1));
	Wall7->SetRelativeLocation(FVector(0.f, 0.f, ZLocation1));

	// Set second wallset positions
	Wall4->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));
	Wall10->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));

	// Check if its time to reset the height
	if(FMath::IsNearlyZero(TimelinePosition - .5f, 0.01f) && !bHalfEvent1)
	{
		bHalfEvent1 = true; // Establish that half event happened
		Height1_7 = GetRandomInt(); // Set new height
		Movement1->Timeline->SetPlayRate(FMath::RandRange(1/MaxDuration, 1/MinDuration)); // Set new playrate
	}
	else if(TimelinePosition > .51f && !bHalfEvent1)
	{
		bHalfEvent1 = true; // Establish that half event happened
		Height1_7 = GetRandomInt(); // Set new height
		Movement1->Timeline->SetPlayRate(FMath::RandRange(1/MaxDuration, 1/MinDuration)); // Set new playrate
	}
}

// Function to move the second set of walls with movement2
void AAObstacle14::MoveSecondSet(float FirstValue)
{
	float TimelinePosition = Movement2->Timeline->GetPlaybackPosition();

	// Get the z locations to apply
	float ZLocation1 = Height2_8 * FirstValue;
	float ZLocation2 = Height5_11 * SecondCurve->GetFloatValue(TimelinePosition);

	// Set first wallset positions
	Wall2->SetRelativeLocation(FVector(0.f, 0.f, ZLocation1));
	Wall8->SetRelativeLocation(FVector(0.f, 0.f, ZLocation1));

	// Set second wallset positions
	Wall5->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));
	Wall11->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));

	// Check if its time to reset the height
	if(FMath::IsNearlyZero(TimelinePosition - .5f, 0.01f) && !bHalfEvent2)
	{
		bHalfEvent2 = true; // Establish that half event happened
		Height2_8 = GetRandomInt(); // Set new height
		Movement2->Timeline->SetPlayRate(FMath::RandRange(1/MaxDuration, 1/MinDuration)); // Set new playrate
	}
	else if(TimelinePosition > .51f && !bHalfEvent2)
	{
		bHalfEvent2 = true; // Establish that half event happened
		Height2_8 = GetRandomInt(); // Set new height
		Movement2->Timeline->SetPlayRate(FMath::RandRange(1/MaxDuration, 1/MinDuration)); // Set new playrate
	}
}

// Function to move the third set of walls with movement3
void AAObstacle14::MoveThirdSet(float FirstValue)
{
	float TimelinePosition = Movement3->Timeline->GetPlaybackPosition();

	// Get the z locations to apply
	float ZLocation1 = Height3_9 * FirstValue;
	float ZLocation2 = Height6_12 * SecondCurve->GetFloatValue(TimelinePosition);

	// Set first wallset positions
	Wall3->SetRelativeLocation(FVector(0.f, 0.f, ZLocation1));
	Wall9->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));

	// Set second wallset positions
	Wall6->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));
	Wall12->SetRelativeLocation(FVector(0.f, 0.f, ZLocation2));

	// Check if its time to reset the height
	if(FMath::IsNearlyZero(TimelinePosition - .5f, 0.01f) && !bHalfEvent3)
	{
		bHalfEvent3 = true; // Establish that half event happened
		Height3_9 = GetRandomInt(); // Set new height
		Movement3->Timeline->SetPlayRate(FMath::RandRange(1/MaxDuration, 1/MinDuration)); // Set new playrate
	}
	else if(TimelinePosition > .51f && !bHalfEvent3)
	{
		bHalfEvent3 = true; // Establish that half event happened
		Height3_9 = GetRandomInt(); // Set new height
		Movement3->Timeline->SetPlayRate(FMath::RandRange(1/MaxDuration, 1/MinDuration)); // Set new playrate
	}
}

// Function to be called when the first timeline is finished
void AAObstacle14::FinishedFirstSet()
{
	bHalfEvent1 = false; // Establish that half event hasn't happened
	Height4_10 = GetRandomInt();
	Movement1->Timeline->PlayFromStart(); // Restart the timeline
}

// Function to be called when the second timeline is finished
void AAObstacle14::FinishedSecondSet()
{
	bHalfEvent2 = false; // Establish that half event hasn't happened
	Height5_11 = GetRandomInt();
	Movement2->Timeline->PlayFromStart(); // Restart the timeline
}

// Function to be called when the third timeline is finished
void AAObstacle14::FinishedThirdSet()
{
	bHalfEvent3 = false; // Establish that half event hasn't happened
	Height6_12 = GetRandomInt();
	Movement3->Timeline->PlayFromStart(); // Restart the timeline
}

// Function to get a random integer
float AAObstacle14::GetRandomInt()
{
	return FMath::RandRange(-MaxDisplacement, -MinDisplacement);
}

// Function to be called on initialize collision overlap
void AAObstacle14::OnInitialCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != HitComponent->PlayerRef) // Check if overlapping actor is our player
	{
		return;
	}

	RotationComponent->bActivated = true; // Start rotating
	bWorking = true; // Set working to true

	// Make sure movement timelines are working
	if(!Movement1->Timeline->IsPlaying())
	{
		Movement1->Timeline->Play();
	}

	if(!Movement2->Timeline->IsPlaying())
	{
		Movement2->Timeline->Play();
	}

	if(!Movement3->Timeline->IsPlaying())
	{
		Movement3->Timeline->Play();
	}
}

// Function to be called on capsule collision overlap
void AAObstacle14::OnEndCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor != HitComponent->PlayerRef || !bWorking) // Check if overlapping actor is our player
	{
		return;
	}

	RotationComponent->bActivated = false; // Stop rotating
	bWorking = false; // Set working to false

	// Make sure movement timelines are not working
	if(Movement1->Timeline->IsPlaying())
	{
		Movement1->Timeline->Stop();
	}

	if(Movement2->Timeline->IsPlaying())
	{
		Movement2->Timeline->Stop();
	}

	if(Movement3->Timeline->IsPlaying())
	{
		Movement3->Timeline->Stop();
	}
}
