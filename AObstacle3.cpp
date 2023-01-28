// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle3.h"
#include "ACMeshRotation.h"
#include "ACMeshHit.h"

// Sets default values
AAObstacle3::AAObstacle3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Intialize the static meshes
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle's base mesh"));
	RootComponent = Base;

	HitMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First hit mesh"));
	HitMesh1->SetupAttachment(RootComponent);

	HitMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second hit mesh"));
	HitMesh2->SetupAttachment(RootComponent);

	HitMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Third hit mesh"));
	HitMesh3->SetupAttachment(RootComponent);

	Fruit1_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First fruit, first mesh"));
	Fruit1_1->SetupAttachment(HitMesh1);

	Fruit1_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second fruit, first mesh"));
	Fruit1_2->SetupAttachment(HitMesh1);

	Fruit2_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First fruit, second mesh"));
	Fruit2_1->SetupAttachment(HitMesh2);

	Fruit2_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second fruit, second mesh"));
	Fruit2_2->SetupAttachment(HitMesh2);

	Fruit3_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First fruit, third mesh"));
	Fruit3_1->SetupAttachment(HitMesh3);

	Fruit3_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second fruit, third mesh"));
	Fruit3_2->SetupAttachment(HitMesh3);

	// Initialize the actor components
	Mesh13RotationComp = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component for meshes 1 and 3"));
	Mesh2RotationComp = CreateDefaultSubobject<UACMeshRotation>(TEXT("Rotation component for second mesh"));

	MeshHitComp = CreateDefaultSubobject<UACMeshHit>(TEXT("Hit component for hitting meshes"));

}

// Called when the game starts or when spawned
void AAObstacle3::BeginPlay()
{
	Super::BeginPlay();

	// Set meshes to rotate
	Mesh13RotationComp->AddToRotate(HitMesh1);
	Mesh13RotationComp->AddToRotate(HitMesh3);
	Mesh2RotationComp->AddToRotate(HitMesh2);

	// Set meshes to hit
	MeshHitComp->AddToHit(HitMesh1);
	MeshHitComp->AddToHit(HitMesh2);
	MeshHitComp->AddToHit(HitMesh3);
	
}

// Called every frame
void AAObstacle3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

