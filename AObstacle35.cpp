// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle35.h"
#include "ACMeshRotation.h"
#include "ACMeshHit.h"
#include "ACMeshDisplacement.h"
#include "COBase.h"

// Sets default values
AAObstacle35::AAObstacle35()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root component"));
	SetRootComponent(Wall);

	Cross1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 1"));
	Cross1->SetupAttachment(Wall);
	Cross2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 2"));
	Cross2->SetupAttachment(Wall);
	Cross3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 3"));
	Cross3->SetupAttachment(Wall);
	Cross4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 4"));
	Cross4->SetupAttachment(Wall);
	Cross5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 5"));
	Cross5->SetupAttachment(Wall);
	Cross6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 6"));
	Cross6->SetupAttachment(Wall);
	Cross7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 7"));
	Cross7->SetupAttachment(Wall);
	Cross8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 8"));
	Cross8->SetupAttachment(Wall);
	Cross9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 9"));
	Cross9->SetupAttachment(Wall);
	Cross10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cross 10"));
	Cross10->SetupAttachment(Wall);

	Gear1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 1"));
	Gear1->SetupAttachment(Wall);
	Gear2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 2"));
	Gear2->SetupAttachment(Wall);
	Gear3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 3"));
	Gear3->SetupAttachment(Wall);
	Gear4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 4"));
	Gear4->SetupAttachment(Wall);
	Gear5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 5"));
	Gear5->SetupAttachment(Wall);
	Gear6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 6"));
	Gear6->SetupAttachment(Wall);
	Gear7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 7"));
	Gear7->SetupAttachment(Wall);
	Gear8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 8"));
	Gear8->SetupAttachment(Wall);
	Gear9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 9"));
	Gear9->SetupAttachment(Wall);
	Gear10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating gear 10"));
	Gear10->SetupAttachment(Wall);

	Cylinder1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder 1"));
	Cylinder1->SetupAttachment(Wall);
	Cylinder2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder 2"));
	Cylinder2->SetupAttachment(Wall);
	Cylinder3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder 3"));
	Cylinder3->SetupAttachment(Wall);
	Cylinder4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder 4"));
	Cylinder4->SetupAttachment(Wall);
	Cylinder5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder 5"));
	Cylinder5->SetupAttachment(Wall);

	// Initialize function components
	RotationComponent = CreateDefaultSubobject<UACMeshRotation>(TEXT("Component to rotate crosses and gears"));
	HitComp = CreateDefaultSubobject<UACMeshHit>(TEXT("Component to hit with gears and cylinders"));
	Cross1Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 1"));
	Cross2Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 2"));
	Cross3Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 3"));
	Cross4Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 4"));
	Cross5Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 5"));
	Cross6Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 6"));
	Cross7Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 7"));
	Cross8Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 8"));
	Cross9Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 9"));
	Cross10Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cross 10"));
	Cylinder1Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cylinder 1"));
	Cylinder2Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cylinder 2"));
	Cylinder3Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cylinder 3"));
	Cylinder4Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cylinder 4"));
	Cylinder5Displacement = CreateDefaultSubobject<UACMeshDisplacement>(TEXT("Component to move cylinder 5"));

}

// Called when the game starts or when spawned
void AAObstacle35::BeginPlay()
{
	Super::BeginPlay();

	// Set components to hit
	if(true)
	{
		HitComp->AddToHit(Gear1);
		HitComp->AddToHit(Gear2);
		HitComp->AddToHit(Gear3);
		HitComp->AddToHit(Gear4);
		HitComp->AddToHit(Gear5);
		HitComp->AddToHit(Gear6);
		HitComp->AddToHit(Gear7);
		HitComp->AddToHit(Gear8);
		HitComp->AddToHit(Gear9);
		HitComp->AddToHit(Gear10);
		HitComp->AddToHit(Cylinder1);
		HitComp->AddToHit(Cylinder2);
		HitComp->AddToHit(Cylinder3);
		HitComp->AddToHit(Cylinder4);
		HitComp->AddToHit(Cylinder5);
	}

	// Set components to rotate
	if(true)
	{
		RotationComponent->AddToRotate(Cross1);
		RotationComponent->AddToRotate(Cross2);
		RotationComponent->AddToRotate(Cross3);
		RotationComponent->AddToRotate(Cross4);
		RotationComponent->AddToRotate(Cross5);
		RotationComponent->AddToRotate(Cross6);
		RotationComponent->AddToRotate(Cross7);
		RotationComponent->AddToRotate(Cross8);
		RotationComponent->AddToRotate(Cross9);
		RotationComponent->AddToRotate(Cross10);
		RotationComponent->AddToRotate(Gear1);
		RotationComponent->AddToRotate(Gear2);
		RotationComponent->AddToRotate(Gear3);
		RotationComponent->AddToRotate(Gear4);
		RotationComponent->AddToRotate(Gear5);
		RotationComponent->AddToRotate(Gear6);
		RotationComponent->AddToRotate(Gear7);
		RotationComponent->AddToRotate(Gear8);
		RotationComponent->AddToRotate(Gear9);
		RotationComponent->AddToRotate(Gear10);
	}

	// Set meshes to displace
	if(true)
	{
		Cross1Displacement->SetHandlingMesh(Cross1);
		Cross2Displacement->SetHandlingMesh(Cross2);
		Cross3Displacement->SetHandlingMesh(Cross3);
		Cross4Displacement->SetHandlingMesh(Cross4);
		Cross5Displacement->SetHandlingMesh(Cross5);
		Cross6Displacement->SetHandlingMesh(Cross6);
		Cross7Displacement->SetHandlingMesh(Cross7);
		Cross8Displacement->SetHandlingMesh(Cross8);
		Cross9Displacement->SetHandlingMesh(Cross9);
		Cross10Displacement->SetHandlingMesh(Cross10);
		Cylinder1Displacement->SetHandlingMesh(Cylinder1);
		Cylinder2Displacement->SetHandlingMesh(Cylinder2);
		Cylinder3Displacement->SetHandlingMesh(Cylinder3);
		Cylinder4Displacement->SetHandlingMesh(Cylinder4);
		Cylinder5Displacement->SetHandlingMesh(Cylinder5);
	}

	// Set player reference
	PlayerRef = HitComp->PlayerRef;

	// Bind functions to events
	if(true)
	{
		Cross1->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross2->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross3->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross4->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross5->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross6->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross7->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross8->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross9->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
		Cross10->OnComponentHit.AddDynamic(this, &AAObstacle35::OnCrossHit);
	}
}

// Called every frame
void AAObstacle35::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called on cross hit
void AAObstacle35::OnCrossHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == PlayerRef)
	{
		PlayerRef->CC_Respawn();
	}
}
