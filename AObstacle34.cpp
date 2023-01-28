// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle34.h"
#include "Components/CapsuleComponent.h"
#include "ACOneCurveTimeline.h"
#include "COBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "ACMeshHit.h"

// Sets default values
AAObstacle34::AAObstacle34()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root component"));
	SetRootComponent(Platform);

	Petal1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 1"));
	Petal1->SetupAttachment(Platform);

	Petal2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 2"));
	Petal2->SetupAttachment(Platform);

	Petal3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 3"));
	Petal3->SetupAttachment(Platform);

	Petal4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 4"));
	Petal4->SetupAttachment(Platform);

	Petal5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 5"));
	Petal5->SetupAttachment(Platform);

	Petal6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 6"));
	Petal6->SetupAttachment(Platform);

	Petal7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petal mesh 7"));
	Petal7->SetupAttachment(Platform);

	InitialCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to close petals"));
	InitialCollision->SetupAttachment(Platform);

	InsideCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to see if player is trapped"));
	InsideCollision->SetupAttachment(Platform);

	// Initialize function components
	OpenTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to close petals"));
	HitComp = CreateDefaultSubobject<UACMeshHit>(TEXT("Petal hitting component"));

	// Set variables default values
	Delay = 0.f;
	bPlayerInObstacle = false;
	bPlayerInside = false;
	bTimelinePlay = false;
	bActivated = false;
	Aperture = 60.f;

}

// Called when the game starts or when spawned
void AAObstacle34::BeginPlay()
{
	Super::BeginPlay();

	// Bind functions to events
	OpenTl->OnTimelineTickDel.AddUObject(this, &AAObstacle34::OnOpenTlTick);
	OpenTl->OnTimelineFinishedDel.AddUObject(this, &AAObstacle34::OnOpenTlFinished);
	InitialCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle34::OnInitialBeginOverlap);
	InitialCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle34::OnInitialEndOverlap);
	InsideCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle34::OnInsideBeginOverlap);
	InsideCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle34::OnInsideEndOverlap);
	Platform->OnComponentHit.AddDynamic(this, &AAObstacle34::OnPlatformHit);

	// Set Player reference
	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Set meshes to hit
	HitComp->AddToHit(Petal1);
	HitComp->AddToHit(Petal2);
	HitComp->AddToHit(Petal3);
	HitComp->AddToHit(Petal4);
	HitComp->AddToHit(Petal5);
	HitComp->AddToHit(Petal6);
	HitComp->AddToHit(Petal7);
	
}

// Called every frame
void AAObstacle34::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called on OpenTl Tick
void AAObstacle34::OnOpenTlTick(float Value)
{
	Petal1->SetRelativeRotation(FRotator(-Value*Aperture, 0.f, 0.f));
	Petal2->SetRelativeRotation(FRotator(-Value*Aperture, 51.42857f, 0.f));
	Petal3->SetRelativeRotation(FRotator(-Value*Aperture, 102.85714f, 0.f));
	Petal4->SetRelativeRotation(FRotator(-Value*Aperture, 154.285721f, 0.f));
	Petal5->SetRelativeRotation(FRotator(-Value*Aperture, 205.714249f, 0.f));
	Petal6->SetRelativeRotation(FRotator(-Value*Aperture, 257.142853f, 0.f));
	Petal7->SetRelativeRotation(FRotator(-Value*Aperture, 308.571442f, 0.f));
}

// Function to be called on OpenTl Finished
void AAObstacle34::OnOpenTlFinished()
{
	if(bPlayerInside)
	{
		PlayerRef->CC_Respawn();
	}

	if(bTimelinePlay)
	{
		bTimelinePlay = false;
		OpenTl->Timeline->Reverse();
		bActivated = false;
	}

}

// Function to be called on Initial collision begin overlap
void AAObstacle34::OnInitialBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == PlayerRef)
	{
		bPlayerInObstacle = true;
	}
}

// Function to be called on Initial collision end overlap
void AAObstacle34::OnInitialEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == PlayerRef)
	{
		bPlayerInObstacle = false;
		OpenTl->Timeline->Reverse();
	}

}

// Function to be called on Platform hit
void AAObstacle34::OnPlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!bActivated)
	{
		bActivated = true;
		FTimerHandle StartClosingHandle;
		GetWorldTimerManager().SetTimer(StartClosingHandle, this, &AAObstacle34::StartClosing, Delay + 0.1f, false);
	}
}

// Function to start closing the petals
void AAObstacle34::StartClosing()
{
	OpenTl->PlayTimelineFromStart();
	bTimelinePlay = true;
}

// Function to be called when player is inside the flower
void AAObstacle34::OnInsideBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == PlayerRef)
	{
		bPlayerInside = true;
	}
}

// Function to be called when player leaves the inside of flower
void AAObstacle34::OnInsideEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == PlayerRef)
	{
		bPlayerInside = false;
	}
}
