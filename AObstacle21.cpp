// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle21.h"
#include "Components/BoxComponent.h"
#include "ACMeshHit.h"
#include "ACMeshRotation.h"
#include "ACOneCurveTimeline.h"
#include "COBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAObstacle21::AAObstacle21()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root component"));
	SetRootComponent(Base);

	Cone1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone one"));
	Cone1->SetupAttachment(Base);

	Cone2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone two"));
	Cone2->SetupAttachment(Base);

	Cone3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone three"));
	Cone3->SetupAttachment(Base);

	Cone4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone four"));
	Cone4->SetupAttachment(Base);

	Cone5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone five"));
	Cone5->SetupAttachment(Base);

	Cone6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone six"));
	Cone6->SetupAttachment(Base);

	BallBase1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First ball base"));
	BallBase1->SetupAttachment(Base);

	BallBase2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second ball base"));
	BallBase2->SetupAttachment(Base);

	BallRope1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First ball rope"));
	BallRope1->SetupAttachment(BallBase1);

	BallRope2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second ball rope"));
	BallRope2->SetupAttachment(BallBase2);

	Ball1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First ball"));
	Ball1->SetupAttachment(BallRope1);

	Ball2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second ball"));
	Ball2->SetupAttachment(BallRope2);
	
	EntranceCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Entrance collision"));
	EntranceCollision->SetupAttachment(Base);

	// Initialize function components
	ConeHitComponent = CreateDefaultSubobject<UACMeshHit>(TEXT("Cone hit component"));
	BallHitComponent = CreateDefaultSubobject<UACMeshHit>(TEXT("Ball hit component"));
	BallMovement1Tl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move first ball"));
	BallMovement2Tl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move second ball"));
	RotationComponent = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component"));

	// Set variables default values
	GroundFriction = 0.f;

}

// Called when the game starts or when spawned
void AAObstacle21::BeginPlay()
{
	Super::BeginPlay();

	// Initialize function components
	ConeHitComponent->AddToHit(Cone1);
	ConeHitComponent->AddToHit(Cone2);
	ConeHitComponent->AddToHit(Cone3);
	ConeHitComponent->AddToHit(Cone4);
	ConeHitComponent->AddToHit(Cone5);
	ConeHitComponent->AddToHit(Cone6);
	BallHitComponent->AddToHit(Ball1);
	BallHitComponent->AddToHit(Ball2);
	RotationComponent->AddToRotate(Cone1);
	RotationComponent->AddToRotate(Cone2);
	RotationComponent->AddToRotate(Cone3);
	RotationComponent->AddToRotate(Cone4);
	RotationComponent->AddToRotate(Cone5);
	RotationComponent->AddToRotate(Cone6);

	// Bind functions
	BallMovement1Tl->OnTimelineTickDel.AddUObject(this, &AAObstacle21::OnBallMovement1Tick);
	BallMovement2Tl->OnTimelineTickDel.AddUObject(this, &AAObstacle21::OnBallMovement2Tick);
	EntranceCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle21::OnCollisionBeginOverlap);
	EntranceCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle21::OnCollisionEndOverlap);

	// Set the player reference
	PlayerRef = ConeHitComponent->PlayerRef;
	
}

// Called every frame
void AAObstacle21::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called on ball movement 1 timeline
void AAObstacle21::OnBallMovement1Tick(float Value)
{
	BallBase1->SetRelativeRotation(FRotator(0.f, 0.f, Value));
}

// Function to be called on ball movement 2 timeline
void AAObstacle21::OnBallMovement2Tick(float Value)
{
	BallBase2->SetRelativeRotation(FRotator(0.f, 0.f, Value));
}

// Function to trigger on collision entrance
void AAObstacle21::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	PlayerRef->GetCharacterMovement()->GroundFriction = GroundFriction;
}

// Function to trigger on collision end overlap
void AAObstacle21::OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	if(OtherActor != PlayerRef)
	{
		return;
	}

	PlayerRef->GetCharacterMovement()->GroundFriction = 13.f;
}

