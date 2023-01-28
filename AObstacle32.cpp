// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle32.h"
#include "ACOneCurveTimeline.h"
#include "ACMeshHit.h"
#include "COBase.h"

// Sets default values
AAObstacle32::AAObstacle32()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring mesh"));
	SetRootComponent(Base);

	Blade1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 1"));
	Blade1->SetupAttachment(Base);

	Blade2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 2"));
	Blade2->SetupAttachment(Base);

	Blade3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 3"));
	Blade3->SetupAttachment(Base);

	Blade4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 4"));
	Blade4->SetupAttachment(Base);

	Blade5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 5"));
	Blade5->SetupAttachment(Base);

	Blade6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 6"));
	Blade6->SetupAttachment(Base);

	Blade7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 7"));
	Blade7->SetupAttachment(Base);

	Blade8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 8"));
	Blade8->SetupAttachment(Base);

	Blade9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 9"));
	Blade9->SetupAttachment(Base);

	Blade10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 10"));
	Blade10->SetupAttachment(Base);

	Blade11 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 11"));
	Blade11->SetupAttachment(Base);

	Blade12 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade 12"));
	Blade12->SetupAttachment(Base);

	// Initialize function components
	OpenTimeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Component to open the blades"));
	HittingComponent = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component"));

	// Set variable default values
	HoleAperture = 50.f;

}

// Called when the game starts or when spawned
void AAObstacle32::BeginPlay()
{
	Super::BeginPlay();

	// Set initial Yaw Rotation
	Blade1InitialYaw = Blade1->GetRelativeRotation().Yaw;
	Blade2InitialYaw = Blade2->GetRelativeRotation().Yaw;
	Blade3InitialYaw = Blade3->GetRelativeRotation().Yaw;
	Blade4InitialYaw = Blade4->GetRelativeRotation().Yaw;
	Blade5InitialYaw = Blade5->GetRelativeRotation().Yaw;
	Blade6InitialYaw = Blade6->GetRelativeRotation().Yaw;
	Blade7InitialYaw = Blade7->GetRelativeRotation().Yaw;
	Blade8InitialYaw = Blade8->GetRelativeRotation().Yaw;
	Blade9InitialYaw = Blade9->GetRelativeRotation().Yaw;
	Blade10InitialYaw = Blade10->GetRelativeRotation().Yaw;
	Blade11InitialYaw = Blade11->GetRelativeRotation().Yaw;
	Blade12InitialYaw = Blade12->GetRelativeRotation().Yaw;

	// Set component to hit
	HittingComponent->AddToHit(Base);

	// Bind functions to events
	Blade1->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade2->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade3->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade4->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade5->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade6->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade7->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade8->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade9->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade10->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade11->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);
	Blade12->OnComponentHit.AddDynamic(this, &AAObstacle32::OnBladeHit);

	OpenTimeline->OnTimelineTickDel.AddUObject(this, &AAObstacle32::OnOpenTlTick);

	// Set player reference
	PlayerRef = HittingComponent->PlayerRef;
}

// Called every frame
void AAObstacle32::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called when local player touches any blade
void AAObstacle32::OnBladeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == PlayerRef)
	{
		PlayerRef->CC_Respawn();
	}
}

// Function to be called on OpenTimeline Tick
void AAObstacle32::OnOpenTlTick(float Value)
{
	Blade1->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade1InitialYaw, 3.f));
	Blade2->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade2InitialYaw, 3.f));
	Blade3->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade3InitialYaw, 3.f));
	Blade4->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade4InitialYaw, 3.f));
	Blade5->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade5InitialYaw, 3.f));
	Blade6->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade6InitialYaw, 3.f));
	Blade7->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade7InitialYaw, 3.f));
	Blade8->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade8InitialYaw, 3.f));
	Blade9->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade9InitialYaw, 3.f));
	Blade10->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade10InitialYaw, 3.f));
	Blade11->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade11InitialYaw, 3.f));
	Blade12->SetRelativeRotation(FRotator(0.f, Value*HoleAperture + Blade12InitialYaw, 3.f));
}
