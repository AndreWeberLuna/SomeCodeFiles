// Fill out your copyright notice in the Description page of Project Settings.

#include "AObstacle37.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "COBase.h"

// Sets default values
AAObstacle37::AAObstacle37()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	TargetWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall containing targets"));
	TargetWall->SetupAttachment(Root);

	BaseFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh to respawn in"));
	BaseFloor->SetupAttachment(Root);

	Target1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First target"));
	Target1->SetupAttachment(TargetWall);

	Target2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second target"));
	Target2->SetupAttachment(TargetWall);

	Target3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third target"));
	Target3->SetupAttachment(TargetWall);

	Target4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fourth target"));
	Target4->SetupAttachment(TargetWall);

	Target5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fifth target"));
	Target5->SetupAttachment(TargetWall);

	Target6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sixth target"));
	Target6->SetupAttachment(TargetWall);

	Swing = CreateDefaultSubobject<UChildActorComponent>(TEXT("Swing actor"));
	Swing->SetupAttachment(Root);

	BlockCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to prevent player from passing"));
	BlockCollision->SetupAttachment(Root);

	// Set variables default values
	TargetNum = 5;
	TargetHits = 0;

}

// Called when the game starts or when spawned
void AAObstacle37::BeginPlay()
{
	Super::BeginPlay();

	// Set Player Reference
	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Bind functions to events
	Target1->OnComponentHit.AddDynamic(this, &AAObstacle37::OnTargetHit);
	Target2->OnComponentHit.AddDynamic(this, &AAObstacle37::OnTargetHit);
	Target3->OnComponentHit.AddDynamic(this, &AAObstacle37::OnTargetHit);
	Target4->OnComponentHit.AddDynamic(this, &AAObstacle37::OnTargetHit);
	Target5->OnComponentHit.AddDynamic(this, &AAObstacle37::OnTargetHit);
	Target6->OnComponentHit.AddDynamic(this, &AAObstacle37::OnTargetHit);
	TargetWall->OnComponentHit.AddDynamic(this, &AAObstacle37::OnWallHit);
	
}

// Called every frame
void AAObstacle37::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to be called on Target hit
void AAObstacle37::OnTargetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	UStaticMeshComponent* Target = Cast<UStaticMeshComponent>(HitComponent);
	Target->SetStaticMesh(nullptr);

	TargetHits++;
	if(TargetHits == TargetNum)
	{
		BlockCollision->SetCollisionProfileName(FName("NoCollision"));
	}

	PlayerRef->CC_Respawn();

}

// Function to be called on Wall hit
void AAObstacle37::OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == PlayerRef)
	{
		PlayerRef->CC_Respawn();
	}
}

