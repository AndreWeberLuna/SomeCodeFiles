// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle8V1.h"
#include "COBase.h"

AAObstacle8V1::AAObstacle8V1()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // Initialize components

    Trampoline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Launching Trampoline"));
    Trampoline->SetupAttachment(RootComponent);
    Trampoline->OnComponentHit.AddDynamic(this, &AAObstacle8V1::OnTrampolineHit);
}

void AAObstacle8V1::BeginPlay()
{
    Super::BeginPlay();
    
}

// Function to fire on Trampoline player's Hit
void AAObstacle8V1::OnTrampolineHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if(PlayerRef == OtherActor)
    {
        PlayerRef->CC_OnObstacleHit(FVector(0.f, 0.f, TrampolineHitForce), 0.f, false, Hit.Location);
    }

}