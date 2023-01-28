// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle12.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "ACOneCurveTimeline.h"
#include "Kismet/KismetArrayLibrary.h"
#include "COBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAObstacle12::AAObstacle12()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	Platform1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number one"));
	Platform1->SetupAttachment(Root);

	Platform2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number two"));
	Platform2->SetupAttachment(Root);

	Platform3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number three"));
	Platform3->SetupAttachment(Root);

	Platform4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number four"));
	Platform4->SetupAttachment(Root);

	Platform5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number five"));
	Platform5->SetupAttachment(Root);

	Platform6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number six"));
	Platform6->SetupAttachment(Root);

	Platform7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number seven"));
	Platform7->SetupAttachment(Root);

	Platform8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number eigth"));
	Platform8->SetupAttachment(Root);

	Platform9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform number nine"));
	Platform9->SetupAttachment(Root);

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button to press"));
	Button->SetupAttachment(Root);

	EntranceCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to start"));
	EntranceCollision->SetupAttachment(Root);

	ExitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to block the exit"));
	ExitCollision->SetupAttachment(Root);

	FloorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("First floor collision"));
	FloorCollision->SetupAttachment(Root);

	FloorCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Second floor collision"));
	FloorCollision2->SetupAttachment(Root);

	ButtonCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Button collision"));
	ButtonCollision->SetupAttachment(Button);

	// Initialize function components

	ShowBlockTimeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to show blocks"));
	ButtonTimeline = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to handle button"));

	// Initialize variables

	bCompleted = false;
	bWorking = true;
	BlockCount = 0;
	BlockCount2 = 0;
	bEnabledBlock1 = true;
	bEnabledBlock2 = false;
	bPressed = false;
	CountVar = 0;
	BlockNum = 9;

}

// Called when the game starts or when spawned
void AAObstacle12::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to our player
	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Bind all the timelines to functions
	ShowBlockTimeline->OnTimelineTickDel.AddUObject(this, &AAObstacle12::OnBlockTlTick);
	ShowBlockTimeline->OnTimelineFinishedDel.AddUObject(this, &AAObstacle12::OnBlockTlFinished);

	ButtonTimeline->OnTimelineTickDel.AddUObject(this, &AAObstacle12::OnButtonTlTick);
	ButtonTimeline->OnTimelineFinishedDel.AddUObject(this, &AAObstacle12::OnButtonTlFinished);

	// Populate the block's array
	BlockArray = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Platform"));
	ShuffleArray(BlockArray);

	// Binding delegates
	EntranceCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle12::OnEntranceOverlap);
	FloorCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle12::OnBlock1Overlap);
	FloorCollision2->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle12::OnBlock2Overlap);
	ButtonCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle12::OnButtonOverlap);
	ButtonCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle12::OnEndButtonOverlap);
	
	// Setting up materials
	MaterialInstance = Platform1->GetMaterial(0);
	EmissiveMaterial = UMaterialInstanceDynamic::Create(MaterialInstance, this);
	EmissiveMaterial->SetScalarParameterValue(TEXT("EmissiveIntensity"), 2.f);
	NonEmissiveMaterial = UMaterialInstanceDynamic::Create(MaterialInstance, this);
	NonEmissiveMaterial->SetScalarParameterValue(TEXT("EmissiveIntensity"), .2f);
}

// Called every frame
void AAObstacle12::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to handle the button timeline tick
void AAObstacle12::OnButtonTlTick(float Value)
{
	FVector InitialLocation = Button->GetRelativeLocation();

	Button->SetRelativeLocation(FVector(InitialLocation.X, InitialLocation.Y, UKismetMathLibrary::Lerp(0.f, -30.f, Value)));
}

// Function to handle the button timeline finished
void AAObstacle12::OnButtonTlFinished()
{
	if(bPressed)
	{
		ResetBlocks();
		bWorking = true;
		CountVar = 0;

		// Start visualizing the order to follow
		VisualizeOrder();
	}
}

// Function to handle the show block timeline tick
void AAObstacle12::OnBlockTlTick(float Value)
{
	UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockArray[CountVar]);
	FVector CurrentLocation = CurrentBlock->GetRelativeLocation();
	CurrentBlock->SetRelativeLocation(FVector(CurrentLocation.X, CurrentLocation.Y, UKismetMathLibrary::Lerp(0.f, 70.f, Value)));
}

// Function to handle the show block timeline finished
void AAObstacle12::OnBlockTlFinished()
{
	UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockArray[CountVar]);
	FVector CurrentLocation = CurrentBlock->GetRelativeLocation();
	CurrentBlock->SetRelativeLocation(FVector(CurrentLocation.X, CurrentLocation.Y, 0.f));

	CountVar++;
	bWorking = true;
	VisualizeOrder();
}

// Function to shuffle an array
void AAObstacle12::ShuffleArray(TArray<UActorComponent*>& Array)
{
	// Get how many times we'll reiterate
	int32 LastIndex = Array.Num() - 1;

	// Go swapping indexes to get 
	for (int32 i = 0; i < Array.Num(); i++)
	{
		int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
		{
			Array.Swap(i, Index);
		}
	}
	
}

// Function to work when the button is overlapped
void AAObstacle12::OnButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef || bCompleted) // Check return condition
	{
		return;
	}

	bPressed = true;

	ButtonTimeline->Timeline->Play();

}

// Function to call when the button ended overlapping
void AAObstacle12::OnEndButtonOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor != PlayerRef || bCompleted) // Check return condition
	{
		return;
	}

	bPressed = false;

	ButtonTimeline->Timeline->Reverse();
}

// Function to call when the entrance collision is overlapped
void AAObstacle12::OnEntranceOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Check if overlapping actor is our player and if the obstacle is completed
	if(OtherActor != PlayerRef || bCompleted)
	{
		return;
	}

	// Stop showing the pattern
	ShowBlockTimeline->Timeline->Stop();

	// Set all the blocks to original position, disable collision and initialize blocks
	ResetBlocks();
	SetBlocksCollision(FName("NoCollison"));
	InitializeBlocks();


}

// Function to call when the first block's collision is overlapped
void AAObstacle12::OnBlock1Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef) // Check if overlapping is the player
	{
		return;
	}

	if(bEnabledBlock1)
	{
		UpdateCollision1();
	}
}

// Function to call when the second block's collision is overlapped
void AAObstacle12::OnBlock2Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor != PlayerRef) // Check if overlapping is the player
	{
		return;
	}

	if(bEnabledBlock2)
	{
		UpdateCollision2();
	}
}

// Function to reset all the blocks
void AAObstacle12::ResetBlocks()
{
	// Iterate on the block array and set ZLocation to 0
	for (auto &Block : BlockArray)
	{
		UStaticMeshComponent* CastedBlock = Cast<UStaticMeshComponent>(Block);
		FVector CurrentLocation = CastedBlock->GetRelativeLocation();
		CastedBlock->SetRelativeLocation(FVector(CurrentLocation.X, CurrentLocation.Y, 0.f));
		CastedBlock->SetMaterial(0, NonEmissiveMaterial);
	}
}

// Set all the blocks to a collision
void AAObstacle12::SetBlocksCollision(FName CollisionName)
{
	// Iterate on the block array and set the new collision
	for (auto &Block : BlockArray)
	{
		UStaticMeshComponent* CastedBlock = Cast<UStaticMeshComponent>(Block);
		CastedBlock->SetCollisionProfileName(CollisionName);
	}
}

// Prepare the blocks to start the obstacle
void AAObstacle12::InitializeBlocks()
{
	// Initialize block counts
	BlockCount = 0;
	BlockCount2 = 1;

	// Initialize first block
	UStaticMeshComponent* Block = Cast<UStaticMeshComponent>(BlockArray[BlockCount]); // Create reference to first element
	if(Block)
	{
		FVector BlockLocation = Block->GetRelativeLocation();
		FloorCollision->SetRelativeLocation(FVector(BlockLocation.X, BlockLocation.Y, 15.f), false); // Change the relative location to match with the first element
		Block->SetCollisionProfileName(FName("BlockAllDynamic")); // Set Collision to block
	}

	// Initialize second block
	UStaticMeshComponent* Block2 = Cast<UStaticMeshComponent>(BlockArray[BlockCount2]); // Create reference to first element
	if(Block2)
	{
		FVector BlockLocation = Block2->GetRelativeLocation();
		FloorCollision2->SetRelativeLocation(FVector(BlockLocation.X, BlockLocation.Y, 15.f), false); // Change the relative location to match with the first element
	}

	// Set the first block to start working
	bEnabledBlock1 = true;
}

// Show the player the order to step in
void AAObstacle12::VisualizeOrder()
{
	if (CountVar < BlockNum && bWorking)
	{
		bWorking = false;
		ShowBlockTimeline->Timeline->PlayFromStart();
	}
	
}

// To handle collision while the player jumps from block to block
void AAObstacle12::UpdateCollision1()
{
	if(!bEnabledBlock1)
	{
		return;
	}

	bEnabledBlock1 = false;

	if(BlockCount == 0)
	{
		// Set emissive material
		UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockArray[0]);
		CurrentBlock->SetMaterial(0, EmissiveMaterial);

		UStaticMeshComponent* Block = Cast<UStaticMeshComponent>(BlockArray[1]);
		Block->SetCollisionProfileName(FName("BlockAllDynamic")); // Change next collision to block
		BlockCount += 2; // Set block count to next block
		bEnabledBlock2 = true; // Enable the next block collision
		FloorCollision2->SetCollisionProfileName(FName("OverlapAllDynamic")); // Activate the next floor collision
	} 
	else if(BlockCount == (BlockNum-1))
	{
		// Set every block to emissive
		for (auto &BlockInArray : BlockArray)
		{
		// Set emissive material
		UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockInArray);
		CurrentBlock->SetMaterial(0, EmissiveMaterial);
		}

		// Disable Exit Collision
		ExitCollision->SetCollisionProfileName(FName("NoCollision"));
		// Make all collision to block
		SetBlocksCollision(FName("BlockAllDynamic"));
		// Set to completed
		bCompleted = true;
	}
	else
	{
		// Set emissive material
		UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockArray[BlockCount]);
		CurrentBlock->SetMaterial(0, EmissiveMaterial);

		// Disable collision on previous block
		UStaticMeshComponent* PrevBlock = Cast<UStaticMeshComponent>(BlockArray[BlockCount-1]);
		PrevBlock->SetCollisionProfileName(FName("NoCollision"));

		// Enable collision on next block
		UStaticMeshComponent* NextBlock = Cast<UStaticMeshComponent>(BlockArray[BlockCount+1]);
		NextBlock->SetCollisionProfileName(FName("BlockAllDynamic"));

		FVector NewLocation = NextBlock->GetRelativeLocation();
		FloorCollision2->SetRelativeLocation(FVector(NewLocation.X, NewLocation.Y, 15.f));
		BlockCount += 2;
		bEnabledBlock2 = true;
	}
}

// To handle the second collision while the player jumps from block to block
void AAObstacle12::UpdateCollision2()
{
	if(!bEnabledBlock2) // Check if it's enabled
	{
		return;
	}

	if((BlockCount2+1) != BlockNum)
	{
		// Set emissive material
		UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockArray[BlockCount2]);
		CurrentBlock->SetMaterial(0, EmissiveMaterial);

		// Change previous block to no collision
		UStaticMeshComponent* PrevBlock = Cast<UStaticMeshComponent>(BlockArray[BlockCount2 - 1]);
		PrevBlock->SetCollisionProfileName(FName("NoCollision"));

		// Enable next block's collision
		UStaticMeshComponent* NextBlock = Cast<UStaticMeshComponent>(BlockArray[BlockCount2 + 1]);
		NextBlock->SetCollisionProfileName(FName("BlockAllDynamic"));

		// Change the collision to the next target and enable it
		FVector NewLocation = NextBlock->GetRelativeLocation();
		FloorCollision->SetRelativeLocation(FVector(NewLocation.X, NewLocation.Y, 15.f));
		BlockCount2 += 2;
		bEnabledBlock1 = true;
	} 
	else
	{
		// Set every block to emissive
		for (auto &BlockInArray : BlockArray)
		{
		// Set emissive material
		UStaticMeshComponent* CurrentBlock = Cast<UStaticMeshComponent>(BlockInArray);
		CurrentBlock->SetMaterial(0, EmissiveMaterial);
		}

		// Disable Exit Collision
		ExitCollision->SetCollisionProfileName(FName("NoCollision"));
		// Make all collision to block
		SetBlocksCollision(FName("BlockAllDynamic"));
		// Set to completed
		bCompleted = true;
	}


}




