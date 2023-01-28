// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle8.h"
#include "ACSplinePath.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "ACMeshRotation.h"
#include "ACMeshHit.h"
#include "ACOneCurveTimeline.h"
#include "Components/TimelineComponent.h"
#include "COBase.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SplineComponent.h"

// Sets default values
AAObstacle8::AAObstacle8()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize the actor's components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root component to be rotated"));
	RootComponent = Base;

	Obstacle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First hitting mesh"));
	Obstacle1->SetupAttachment(Base);

	Obstacle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second hitting mesh"));
	Obstacle2->SetupAttachment(Base);

	Obstacle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third hitting mesh"));
	Obstacle3->SetupAttachment(Base);

	SplineRoute = CreateDefaultSubobject<UACSplinePath>(TEXT("Spline that obstacles will follow"));
	SplineRoute->SetupAttachment(Base);

	StartCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to start the obstacle"));
	StartCollision->SetupAttachment(Base);
	StartCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle8::StartObstacle);

	DeathCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to determine when the player has lost"));
	DeathCollision->SetupAttachment(Base);
	DeathCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle8::RestartObstacle);

	JumpMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Mesh the player will have to jump"));
	CrouchMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Mesh the player will have to crouch"));


	// Initialize actor components
	RotationComp = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component"));
	HitComp = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component"));
	Obs1MovementTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline component for first obstacle"));
	Obs2MovementTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline component for second obstacle"));
	Obs3MovementTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline component for third obstacle"));
	RotationResetTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline component to reset obstacle's rotation"));

	// Create default values for programmer and designer variables
	Obs1Progress = 0.f;
	Obs2Progress = 0.f;
	Obs3Progress = 0.f;
	ZOffset1 = 0.f;
	ZOffset2 = 0.f;
	ZOffset3 = 0.f;
	bEnabledDeathCollision = false;	
	bEnabledObstacle = false;
	NextObstacle = ENextObstacle::ENO_Value1;

	ObstacleSpeed = 0.05f;
	ObstacleFrequency = 0.1f;
	StartProgress = 0.8f;

}

// Called when the game starts or when spawned
void AAObstacle8::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize programmer variables
	PlayerRef = HitComp->PlayerRef;
	InitialRotation = GetActorRotation();

	// Add mesh to rotating meshes
	RotationComp->AddToRotate(Base);

	// Add meshes to hitting meshes
	HitComp->AddToHit(Obstacle1);
	HitComp->AddToHit(Obstacle2);
	HitComp->AddToHit(Obstacle3);

	// Bind our functions to the timeline components
	Obs1MovementTl->OnTimelineTickDel.AddUObject(this, &AAObstacle8::MoveObs1);
	Obs2MovementTl->OnTimelineTickDel.AddUObject(this, &AAObstacle8::MoveObs2);
	Obs3MovementTl->OnTimelineTickDel.AddUObject(this, &AAObstacle8::MoveObs3);
	RotationResetTl->OnTimelineTickDel.AddUObject(this, &AAObstacle8::SetRotation);
	RotationResetTl->OnTimelineFinishedDel.AddUObject(this, &AAObstacle8::OnFinishedRotating);

	// Get the spline length
	SplineLength = SplineRoute->GetSplineLength();

	// Deactivate the rotation component
	RotationComp->bActivated = false;

}

// Called every frame
void AAObstacle8::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Used on Obs1MovementTl tick to move the first obstacle
void AAObstacle8::MoveObs1(float Progress)
{
	// Move obstacle
	float Distance = SplineLength * Progress;
	FRotator NewRotation = SplineRoute->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World); // Rotation at a distance of the spline
	FVector NewLocation = SplineRoute->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World); // Location at a distance of the spline
	NewLocation.Z += ZOffset1;
	Obstacle1->SetWorldLocationAndRotation(NewLocation, NewRotation, true);
	FVector ObstacleLocation = Obstacle1->GetComponentLocation(); // Get Obstacle location
}

// Used on Obs1MovementTl tick to move the second obstacle
void AAObstacle8::MoveObs2(float Progress)
{
	// Move obstacle along spline
	float Distance = SplineLength * Progress;
	FRotator NewRotation = SplineRoute->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World); // Rotation at a distance of the spline
	//NewRotation.Yaw += 180.f; // Rotate 90 degrees the rotation
	FVector NewLocation = SplineRoute->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World); // Location at a distance of the spline
	NewLocation.Z += ZOffset2;
	Obstacle2->SetWorldLocationAndRotation(NewLocation, NewRotation, true);
}

// Used on Obs1MovementTl tick to move the third obstacle
void AAObstacle8::MoveObs3(float Progress)
{
	// Move obstacle along spline
	float Distance = SplineLength * Progress;
	FRotator NewRotation = SplineRoute->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World); // Rotation at a distance of the spline
	FVector NewLocation = SplineRoute->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World); // Location at a distance of the spline
	NewLocation.Z += ZOffset3;
	Obstacle3->SetWorldLocationAndRotation(NewLocation, NewRotation, true);
}

// Used on RotationResetTl tick to move the first obstacle
void AAObstacle8::SetRotation(float Alpha)
{
	// Rotate the base
	SetActorRotation(FMath::Lerp(LastRotation, InitialRotation, Alpha));
}

// Used on RotationResetTl on finished to disable the obstacle
void AAObstacle8::OnFinishedRotating()
{
	SetActorRotation(InitialRotation); // Reset the actor's rotation
	bEnabledObstacle = false; // Disable obstacle
}

// To start the obstacle when the start collision is overlap by our player
void AAObstacle8::StartObstacle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(PlayerRef != OtherActor || bEnabledObstacle) // Check if overlapping actor is my player and if the obstacle's deactivated
	{
		return;
	}

	bEnabledObstacle = true; // Activate the obstacle
	RotationComp->bActivated = true; // Activate the obstacle's rotation
	bEnabledDeathCollision = true; // Activate the death collision
	NextObstacle = ENextObstacle::ENO_Value1; // Restart value to check

	// Set Playrate for the timeline's controlling the obstacle's movement
	SetPlayRate(ObstacleSpeed);

	// Setup the obstacles to start moving
	SetupObstacle(Obs1MovementTl->Timeline, 1, StartProgress, Obstacle1);
	SetupObstacle(Obs2MovementTl->Timeline, 2, StartProgress - ObstacleFrequency, Obstacle2);
	SetupObstacle(Obs3MovementTl->Timeline, 3, StartProgress - (ObstacleFrequency * 2), Obstacle3);

	// Set timer to check when to reposition the obstacles
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AAObstacle8::CheckRespawn, 0.1f, true);
}

// Overload of stop obstacle for when the call isn't from an overlap event
void AAObstacle8::StopObstacle()
{
	// Pause and clear our respawn timer
	GetWorldTimerManager().PauseTimer(RespawnTimerHandle);
	GetWorldTimerManager().ClearTimer(RespawnTimerHandle); 

	bEnabledDeathCollision = false; // Disable death collision

	// Set timer with parameter to end the obstacle's path
	GetWorldTimerManager().SetTimer(SetPlayRateHandle, FTimerDelegate::CreateUObject(this, &AAObstacle8::SetPlayRate, 0.3f), (2*ObstacleFrequency)/ObstacleSpeed, false);
}

// To restart the obstacle when the player loses
void AAObstacle8::RestartObstacle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(PlayerRef != OtherActor || !bEnabledObstacle) // Is the overlapping actor our player and is the obstacle enabled
	{
		return;
	}

	if(bEnabledDeathCollision) // Is the death collision enabled
	{
		/* Respawn player and reset the obstacle */

		PlayerRef->CC_Respawn(); // Respawn our player
		GetWorldTimerManager().PauseTimer(RespawnTimerHandle); // Pause timer to stop respawning obstacles
		GetWorldTimerManager().ClearTimer(RespawnTimerHandle); // Clear timer as we won't use it anymore

		RotationComp->bActivated = false; // Stop rotating our base mesh
		LastRotation = GetActorRotation(); // Safe our last rotation
		RotationResetTl->Timeline->PlayFromStart(); // Start returning to our base to the starting rotation

		// Set timer to end obstacle's path
		GetWorldTimerManager().SetTimer(SetPlayRateHandle, FTimerDelegate::CreateUObject(this, &AAObstacle8::SetPlayRate, 3.f), 0.5f, false);
	}
	else
	{
		/* The player beat the obstacle, while it's in the air, reset the obstacle */

		RotationComp->RotationRate = FRotator(0.f); // Stop rotating our base mesh

		LastRotation = GetActorRotation(); // Safe our last rotation
		RotationResetTl->Timeline->PlayFromStart(); // Start returning to our base to the starting rotation
	}
}

// Function to check if the current obstacle should be respawned
void AAObstacle8::CheckRespawn()
{
	
	// Check which is the obstacle selected and check if it needs to be respawned
	
	switch (NextObstacle)
	{
	case ENextObstacle::ENO_Value1:
	{
		// Check distance or if the obstacle ended its course

		float ClosestInputKey = SplineRoute->FindInputKeyClosestToWorldLocation(PlayerRef->GetActorLocation()); // Get closest input key from the player to the spline
		float PlayerDistance = SplineRoute->GetDistanceAlongSplineAtSplineInputKey(ClosestInputKey) / SplineLength; // Get distance in percentage
		float ObstacleDistance = 1 - Obs1MovementTl->Timeline->GetPlaybackPosition(); // Get distance from the obstacle
		float PlayerObstacleDistance = ObstacleDistance - PlayerDistance; // Distance from the player to the obstacle
		bool bEndedRoute = FMath::IsNearlyEqual(Obs1MovementTl->Timeline->GetPlaybackPosition(), 1.f, 0.01f); // Is the obstacle already on the end of the spline
		
		if(PlayerObstacleDistance < -.10f || bEndedRoute) // If the obstacle is far away or ended the route, respawn it and change selected obstacle to the next one
		{
			if(Obs3MovementTl->Timeline->GetPlaybackPosition() - ObstacleFrequency <= 0)
			{
				StopObstacle();
			}
			else
			{
				float RespawnPosition = Obs3MovementTl->Timeline->GetPlaybackPosition() - ObstacleFrequency;
				SetupObstacle(Obs1MovementTl->Timeline, 1, RespawnPosition, Obstacle1); // Respawn first obstacle in new position
				NextObstacle = ENextObstacle::ENO_Value2;
			}
		}
	}
		break;
	case ENextObstacle::ENO_Value2:
	{
		// Check distance or if the obstacle ended its course

		float ClosestInputKey = SplineRoute->FindInputKeyClosestToWorldLocation(PlayerRef->GetActorLocation()); // Get closest input key from the player to the spline
		float PlayerDistance = SplineRoute->GetDistanceAlongSplineAtSplineInputKey(ClosestInputKey) / SplineLength; // Get distance in percentage
		float ObstacleDistance = 1 - Obs2MovementTl->Timeline->GetPlaybackPosition(); // Get distance from the obstacle
		float PlayerObstacleDistance = ObstacleDistance - PlayerDistance; // Distance from the player to the obstacle
		bool bEndedRoute = FMath::IsNearlyEqual(Obs2MovementTl->Timeline->GetPlaybackPosition(), 1.f, 0.01f); // Is the obstacle already on the end of the spline
		
		if(PlayerObstacleDistance < -.10f || bEndedRoute) // If the obstacle is far away or ended the route, respawn it and change selected obstacle to the next one
		{
			if(Obs1MovementTl->Timeline->GetPlaybackPosition() - ObstacleFrequency <= 0)
			{
				StopObstacle();
			}
			else
			{
				float RespawnPosition = Obs1MovementTl->Timeline->GetPlaybackPosition() - ObstacleFrequency;
				SetupObstacle(Obs2MovementTl->Timeline, 2, RespawnPosition, Obstacle2); // Respawn first obstacle in new position
				NextObstacle = ENextObstacle::ENO_Value3;
			}
		}
	}
		break;
	case ENextObstacle::ENO_Value3:
	{
		// Check distance or if the obstacle ended its course

		float ClosestInputKey = SplineRoute->FindInputKeyClosestToWorldLocation(PlayerRef->GetActorLocation()); // Get closest input key from the player to the spline
		float PlayerDistance = SplineRoute->GetDistanceAlongSplineAtSplineInputKey(ClosestInputKey) / SplineLength; // Get distance in percentage
		float ObstacleDistance = 1 - Obs3MovementTl->Timeline->GetPlaybackPosition(); // Get distance from the obstacle
		float PlayerObstacleDistance = ObstacleDistance - PlayerDistance; // Distance from the player to the obstacle
		bool bEndedRoute = FMath::IsNearlyEqual(Obs3MovementTl->Timeline->GetPlaybackPosition(), 1.f, 0.01f); // Is the obstacle already on the end of the spline
		
		if(PlayerObstacleDistance < -.10f || bEndedRoute)// If the obstacle is far away or ended the route, respawn it and change selected obstacle to the next one
		{
			if(Obs2MovementTl->Timeline->GetPlaybackPosition() - ObstacleFrequency <= 0)
			{
				StopObstacle();
			}
			else
			{
				float RespawnPosition = Obs2MovementTl->Timeline->GetPlaybackPosition() - ObstacleFrequency;
				SetupObstacle(Obs3MovementTl->Timeline, 3, RespawnPosition, Obstacle3); // Respawn first obstacle in new position
				NextObstacle = ENextObstacle::ENO_Value1;
			}
		}
	}
		break;
	default:
		break;
	}
	
}

// Setup an obstacle when respawning
void AAObstacle8::SetupObstacle(UTimelineComponent* TimelineRef, int32 ObsNumber, float PlayPosition, UStaticMeshComponent* Mesh)
{
	TimelineRef->SetPlaybackPosition(PlayPosition, false); // Set the new playback position
	if(!TimelineRef->IsPlaying()) // Make sure the timeline is playing
	{
		TimelineRef->Play();
	}

	int32 RanInt = FMath::RandRange(0, 1); // Get a random int to determine if the obstacle will be for jumping or crouching
	switch (RanInt)
	{
	case 0: // Setup a crouching obstacle
	{
		Mesh->SetStaticMesh(CrouchMesh); 
		switch (ObsNumber) // Change the ZOffset depending on which obstacle it's
		{
		case 1:
			ZOffset1 = 120.f;
			break;

		case 2:
			ZOffset2 = 120.f;
			break;
		
		case 3:
			ZOffset3 = 120.f;
			break;

		default:
			break;
		}
	}
		break;
	
	case 1: // Setup a jumping obstacle
	{
		Mesh->SetStaticMesh(JumpMesh);
		switch (ObsNumber) // Change the ZOffset depending on which obstacle it's
		{
		case 1:
			ZOffset1 = 0.f;
			break;

		case 2:
			ZOffset2 = 0.f;
			break;
		
		case 3:
			ZOffset3 = 0.f;
			break;

		default:
			break;
		}
	}
		break;

	default:
		break;
	};
}

// Set the timeline's play rate
void AAObstacle8::SetPlayRate(float PlayRate)
{
	// Set our timelines' play rate
	Obs1MovementTl->Timeline->SetPlayRate(PlayRate);
	Obs2MovementTl->Timeline->SetPlayRate(PlayRate);
	Obs3MovementTl->Timeline->SetPlayRate(PlayRate);

}

// Set the timeline's to play
void AAObstacle8::PlayTimelines()
{
	Obs1MovementTl->Timeline->Play();
	Obs2MovementTl->Timeline->Play();
	Obs3MovementTl->Timeline->Play();
}



