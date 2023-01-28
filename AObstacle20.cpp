// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle20.h"
#include "COBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "ACOneCurveTimeline.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAObstacle20::AAObstacle20()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	Base->SetupAttachment(Root);

	Rail1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First rail"));
	Rail1->SetupAttachment(Root);

	Rail2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second rail"));
	Rail2->SetupAttachment(Root);

	InitializeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to start"));
	InitializeCollision->SetupAttachment(Base);

	Spline1 = CreateDefaultSubobject<USplineComponent>(TEXT("Spline for hammer1"));
	Spline1->SetupAttachment(Rail1);

	Spline2 = CreateDefaultSubobject<USplineComponent>(TEXT("Spline for hammer2"));
	Spline2->SetupAttachment(Rail2);

	HammerBase1_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First Base for first hammer"));
	HammerBase1_1->SetupAttachment(Rail1);

	HammerBase2_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second Base for first hammer"));
	HammerBase2_1->SetupAttachment(HammerBase1_1);

	HammerBase1_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First Base for second hammer"));
	HammerBase1_2->SetupAttachment(Rail2);

	HammerBase2_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second Base for second hammer"));
	HammerBase2_2->SetupAttachment(HammerBase1_2);

	Hammer1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First hammer mesh"));
	Hammer1->SetupAttachment(HammerBase2_1);

	Hammer2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second hammer mesh"));
	Hammer2->SetupAttachment(HammerBase2_2);

	HitCollision1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to hit on first hammer"));
	HitCollision1->SetupAttachment(HammerBase1_1);

	HitCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to hit on second hammer"));
	HitCollision2->SetupAttachment(HammerBase1_2);

	// Initialize function components
	Hammer1MovementTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move first hammer"));
	Hammer2MovementTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to move second hammer"));
	Swing1Tl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to swing first hammer"));
	Swing2Tl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to swing second hammer"));
	RecoveryTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to handle on end"));

	// Set variables default values
	bWorking = false;

}

// Called when the game starts or when spawned
void AAObstacle20::BeginPlay()
{
	Super::BeginPlay();

	// Bind functions to events
	Hammer1->OnComponentHit.AddDynamic(this, &AAObstacle20::OnHammerHit);
	Hammer2->OnComponentHit.AddDynamic(this, &AAObstacle20::OnHammerHit);

	HitCollision1->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle20::OnFirstCollisionOverlap);
	HitCollision2->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle20::OnSecondCollisionOverlap);

	InitializeCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle20::OnInitialBeginOverlap);
	InitializeCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle20::OnInitialEndOverlap);

	Hammer1MovementTl->OnTimelineTickDel.AddUObject(this, &AAObstacle20::OnMovement1Tick);
	Hammer2MovementTl->OnTimelineTickDel.AddUObject(this, &AAObstacle20::OnMovement2Tick);
	Swing1Tl->OnTimelineTickDel.AddUObject(this, &AAObstacle20::OnSwing1Tick);
	Swing1Tl->OnTimelineFinishedDel.AddUObject(this, &AAObstacle20::OnSwing1Finished);
	Swing2Tl->OnTimelineTickDel.AddUObject(this, &AAObstacle20::OnSwing2Tick);
	Swing2Tl->OnTimelineFinishedDel.AddUObject(this, &AAObstacle20::OnSwing2Finished);
	RecoveryTl->OnTimelineTickDel.AddUObject(this, &AAObstacle20::OnRecoveryTick);

	// Get Player Reference
	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

// Called every frame
void AAObstacle20::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to trigger on hammer hit
void AAObstacle20::OnHammerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if(OtherActor == PlayerRef)
	{
		PlayerRef->CC_Respawn();
	}
}

// Function to trigger on first hammer 
void AAObstacle20::OnFirstCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef || !bCanSwing)
	{
		return;
	}

	// Stop moving hammer and swing it
	Hammer1MovementTl->StopTimeline();
	Swing1Tl->PlayTimelineFromStart();

	// Disable other hammer to swing
	bCanSwing = false;
}

// Function to trigger on second hammer 
void AAObstacle20::OnSecondCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef || !bCanSwing)
	{
		return;
	}

	// Stop moving hammer and swing it
	Hammer2MovementTl->StopTimeline();
	Swing2Tl->PlayTimelineFromStart();

	// Disable other hammer to swing
	bCanSwing = false;
}

// Function to be called on hammer1movement tick
void AAObstacle20::OnMovement1Tick(float Value)
{
	FVector NewLocation = Spline1->GetLocationAtDistanceAlongSpline(Spline1->GetSplineLength() * Value, ESplineCoordinateSpace::World);
	HammerBase1_1->SetWorldLocation(NewLocation);
}

// Function to be called on hammer2movement tick
void AAObstacle20::OnMovement2Tick(float Value)
{
	FVector NewLocation = Spline2->GetLocationAtDistanceAlongSpline(Spline1->GetSplineLength() * Value, ESplineCoordinateSpace::World);
	HammerBase1_2->SetWorldLocation(NewLocation);
}

// Function to be called on swing1 tick
void AAObstacle20::OnSwing1Tick(float Value)
{
	HammerBase2_1->SetRelativeRotation(FRotator(0.f, 0.f, Value));
}

// Function to be called on swing1 finished
void AAObstacle20::OnSwing1Finished()
{
	bool bOverlaping = InitializeCollision->IsOverlappingActor(PlayerRef);
	if(bOverlaping)
	{
		Hammer1MovementTl->PlayTimeline();
		if(bWorking)
		{
			bCanSwing = true;
		}
	}
	else
	{
		bCanSwing = true;
	}
}

// Function to be called on swing2 finished
void AAObstacle20::OnSwing2Finished()
{
	bool bOverlaping = InitializeCollision->IsOverlappingActor(PlayerRef);
	if(bOverlaping)
	{
		Hammer2MovementTl->PlayTimeline();
		if(bWorking)
		{
			bCanSwing = true;
		}
	}
	else
	{
		bCanSwing = true;
	}
}

// Function to be called on swing1 tick
void AAObstacle20::OnSwing2Tick(float Value)
{
	HammerBase2_2->SetRelativeRotation(FRotator(0.f, 0.f, Value));
}

// Function to be called on recovery tick
void AAObstacle20::OnRecoveryTick(float Value)
{
	// Set first hammer location
	FVector Hammer1Location = UKismetMathLibrary::VLerp(Hammer1LastPos, FVector(0.f), Value);
	HammerBase1_1->SetRelativeLocation(Hammer1Location);

	// Set second hammer location
	FVector Hammer2Location = UKismetMathLibrary::VLerp(Hammer2LastPos, FVector(0.f), Value);
	HammerBase1_2->SetRelativeLocation(Hammer2Location);

}

// Function to be called on initialize collision begin overlap
void AAObstacle20::OnInitialBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Start moving hammers
	Hammer1MovementTl->PlayTimelineFromStart();
	Hammer2MovementTl->PlayTimelineFromStart();

	// Change working bool
	bWorking = true;
	bCanSwing = true;
}

// Function to be called on initialize collision end overlap
void AAObstacle20::OnInitialEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	// Stop moving hammers
	Hammer1MovementTl->StopTimeline();
	Hammer2MovementTl->StopTimeline();

	// Save last hammer position
	Hammer1LastPos = HammerBase1_1->GetRelativeLocation();
	Hammer2LastPos = HammerBase1_2->GetRelativeLocation();

	// Start recovering
	RecoveryTl->PlayTimelineFromStart();

	// Set obstacle to off
	bWorking = false;

}

