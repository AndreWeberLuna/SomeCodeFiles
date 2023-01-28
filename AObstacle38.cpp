// Fill out your copyright notice in the Description page of Project Settings.


#include "AObstacle38.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "ACOneCurveTimeline.h" 
#include "COBase.h"
#include "Kismet/GameplayStatics.h"
#include "AIngredient.h"

// Sets default values
AAObstacle38::AAObstacle38()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize scene components
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	BlockCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to disable jump"));
	BlockCollision->SetupAttachment(Root);

	EndCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision to block exit"));
	EndCollision->SetupAttachment(Root);

	Dispenser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh to spawn ingredients"));
	Dispenser->SetupAttachment(Root);

	IngredientSpawnCollision = CreateDefaultSubobject<USceneComponent>(TEXT("Location where ingredients will spawn"));
	IngredientSpawnCollision->SetupAttachment(Dispenser);

	DispenserPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform on the dispenser side"));
	DispenserPlatform->SetupAttachment(Root);

	FunnelPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform on the funnel side"));
	FunnelPlatform->SetupAttachment(Root);

	Funnel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First funnel to receive ingredients"));
	Funnel1->SetupAttachment(FunnelPlatform);

	Funnel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Second funnel to receive ingredients"));
	Funnel2->SetupAttachment(FunnelPlatform);

	Funnel1Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision to detect ingredients for funnel 1"));
	Funnel1Collision->SetupAttachment(Funnel1);

	Funnel2Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision to detect ingredients for funnel 2"));
	Funnel2Collision->SetupAttachment(Funnel2);

	Block1_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 1 column 1"));
	Block1_1->SetupAttachment(Root);

	Block2_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 2 column 1"));
	Block2_1->SetupAttachment(Root);

	Block3_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 3 column 1"));
	Block3_1->SetupAttachment(Root);

	Block4_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 4 column 1"));
	Block4_1->SetupAttachment(Root);

	Block5_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 5 column 1"));
	Block5_1->SetupAttachment(Root);

	Block6_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 6 column 1"));
	Block6_1->SetupAttachment(Root);

	Block1_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 1 column 2"));
	Block1_2->SetupAttachment(Root);

	Block2_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 2 column 2"));
	Block2_2->SetupAttachment(Root);

	Block3_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 3 column 2"));
	Block3_2->SetupAttachment(Root);

	Block4_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 4 column 2"));
	Block4_2->SetupAttachment(Root);

	Block5_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 5 column 2"));
	Block5_2->SetupAttachment(Root);

	Block6_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 6 column 2"));
	Block6_2->SetupAttachment(Root);

	Block1_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 1 column 3"));
	Block1_3->SetupAttachment(Root);

	Block2_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 2 column 3"));
	Block2_3->SetupAttachment(Root);

	Block3_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 3 column 3"));
	Block3_3->SetupAttachment(Root);

	Block4_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 4 column 3"));
	Block4_3->SetupAttachment(Root);

	Block5_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 5 column 3"));
	Block5_3->SetupAttachment(Root);

	Block6_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 6 column 3"));
	Block6_3->SetupAttachment(Root);

	Block1_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 1 column 4"));
	Block1_4->SetupAttachment(Root);

	Block2_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 2 column 4"));
	Block2_4->SetupAttachment(Root);

	Block3_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 3 column 4"));
	Block3_4->SetupAttachment(Root);

	Block4_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 4 column 4"));
	Block4_4->SetupAttachment(Root);

	Block5_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 5 column 4"));
	Block5_4->SetupAttachment(Root);

	Block6_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 6 column 4"));
	Block6_4->SetupAttachment(Root);

	Block1_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 1 column 5"));
	Block1_5->SetupAttachment(Root);

	Block2_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 2 column 5"));
	Block2_5->SetupAttachment(Root);

	Block3_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 3 column 5"));
	Block3_5->SetupAttachment(Root);

	Block4_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 4 column 5"));
	Block4_5->SetupAttachment(Root);

	Block5_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 5 column 5"));
	Block5_5->SetupAttachment(Root);

	Block6_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block in row 6 column 5"));
	Block6_5->SetupAttachment(Root);

	ButtonPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform for the button"));
	ButtonPlatform->SetupAttachment(Root);

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pushable button"));
	Button->SetupAttachment(ButtonPlatform);

	ButtonCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision to push the button"));
	ButtonCollision->SetupAttachment(Button);

	// Initialize function components
	ButtonTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to press button"));
	ShowBlocksTl = CreateDefaultSubobject<UACOneCurveTimeline>(TEXT("Timeline to show block path"));

	// Set variables default values
	NumIngredients = 3;
	DunkedIngredients = 0;
	ButtonPressDistance = 50.f;

}

// Called when the game starts or when spawned
void AAObstacle38::BeginPlay()
{
	Super::BeginPlay();

	// Bind functions to events
	Funnel1Collision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle38::OnFunnelBeginOverlap);
	Funnel2Collision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle38::OnFunnelBeginOverlap);
	ShowBlocksTl->OnTimelineTickDel.AddUObject(this, &AAObstacle38::OnShowBlocksTick);
	ButtonTl->OnTimelineTickDel.AddUObject(this, &AAObstacle38::OnButtonTick);
	BlockCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle38::OnBlockCollisionBeginOverlap);
	BlockCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle38::OnBlockCollisionEndOverlap);
	ButtonCollision->OnComponentBeginOverlap.AddDynamic(this, &AAObstacle38::OnButtonBeginOverlap);
	ButtonCollision->OnComponentEndOverlap.AddDynamic(this, &AAObstacle38::OnButtonEndOverlap);

	// Set player reference
	PlayerRef = Cast<ACOBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Set first block path and spawn first ingredient
	InitializeArrays();
	SetNewPath();
	SpawnIngredient();

	// Set initial button position
	ButtonInitialLocation = Button->GetRelativeLocation();
	
}

// Called every frame
void AAObstacle38::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to initialize arrays
void AAObstacle38::InitializeArrays()
{
	// Fill block array
	BlockArray.Add(Block1_1);
	BlockArray.Add(Block1_2);
	BlockArray.Add(Block1_3);
	BlockArray.Add(Block1_4);
	BlockArray.Add(Block1_5);
	BlockArray.Add(Block2_1);
	BlockArray.Add(Block2_2);
	BlockArray.Add(Block2_3);
	BlockArray.Add(Block2_4);
	BlockArray.Add(Block2_5);
	BlockArray.Add(Block3_1);
	BlockArray.Add(Block3_2);
	BlockArray.Add(Block3_3);
	BlockArray.Add(Block3_4);
	BlockArray.Add(Block3_5);
	BlockArray.Add(Block4_1);
	BlockArray.Add(Block4_2);
	BlockArray.Add(Block4_3);
	BlockArray.Add(Block4_4);
	BlockArray.Add(Block4_5);
	BlockArray.Add(Block5_1);
	BlockArray.Add(Block5_2);
	BlockArray.Add(Block5_3);
	BlockArray.Add(Block5_4);
	BlockArray.Add(Block5_5);
	BlockArray.Add(Block6_1);
	BlockArray.Add(Block6_2);
	BlockArray.Add(Block6_3);
	BlockArray.Add(Block6_4);
	BlockArray.Add(Block6_5);

	// Fill bool array
	for(int32 i = 0; i < 30; i++)
	{
		bWalkableArray.Add(false);
	}

}

// Function to be called when an object begins overlap with funnel collision
void AAObstacle38::OnFunnelBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Cast other actor to ingredient actor and add one to dunked ingredients if true
	if(!Cast<AAIngredient>(OtherActor))
	{
		return;
	}
	else
	{
		DunkedIngredients = DunkedIngredients + 1;
		AAIngredient* DunkedIngredient = Cast<AAIngredient>(OtherActor);
		DunkedIngredient->CC_Destroy();
	}

	if(DunkedIngredients >= NumIngredients)
	{
		EndCollision->SetCollisionProfileName(FName("NoCollision"));
		for (auto Block : BlockArray)
		{
			Block->SetCollisionProfileName(FName("BlockAllDynamic"));
			Block->SetMaterial(2, PassMaterial);
		}
		
	} 
	else 
	{
		for (auto Block : BlockArray)
		{
			Block->SetCollisionProfileName(FName("NoCollision"));
		}

		for(int32 i = 0; i < 30; i++)
		{
			bWalkableArray.Add(false);
		}

		SetNewPath();
	}

}

// Function to show the path on Show Blocks tick
void AAObstacle38::OnShowBlocksTick(float Value)
{
	for (UStaticMeshComponent* &Block : BlockArray)
	{
		Block->SetRelativeRotation(FRotator(Value*180.f, 0.f, 0.f));
	}
	
}

// Function to press the button on button timeline tick
void AAObstacle38::OnButtonTick(float Value)
{
	Button->SetRelativeLocation(FVector(ButtonInitialLocation.X, ButtonInitialLocation.Y, ButtonInitialLocation.Z - (Value*ButtonPressDistance)));
}

// Function to activate timelines on button collision begin overlap
void AAObstacle38::OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	ButtonTl->PlayTimeline();
	ShowBlocksTl->PlayTimeline();
}

// Function to reverse timelines on button collision end overlap
void AAObstacle38::OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor != PlayerRef)
	{
		return;
	}

	ButtonTl->ReverseTimeline();
	ShowBlocksTl->ReverseTimeline();
}

// Function to determine the block path
void AAObstacle38::SetNewPath()
{
	// Set all blocks to no collision blocks
	for (auto Block : BlockArray)
	{
		Block->SetMaterial(2, NoPassMaterial);
		Block->SetCollisionProfileName(FName("NoCollision"));
	}

	// Reset bool array
	for(int32 i = 0; i < 30; i++)
	{
		bWalkableArray[i] = false;
	}

	// Set starting point
	int32 BlockCounter = FMath::RandRange(0, 4);
	BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
	BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
	bWalkableArray[BlockCounter] = true;

	// Create a random path step by step
	while(BlockCounter < 25)
	{
		if(BlockCounter % 5 == 0) // If the block is the most to the left
		{
			int32 Random = FMath::RandRange(1, 2); // Go to the right or up
			if(Random == 1) // Go to the right
			{
				if(!bWalkableArray[BlockCounter+1]) // If right isn't already selected go right
				{
					BlockCounter += 1;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
				else // If right is selected, go up
				{
					BlockCounter += 5;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
			}
			else // Go up
			{
				BlockCounter += 5;
				BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
				BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
				bWalkableArray[BlockCounter] = true;
			}
		}
		else if((BlockCounter+1) % 5 == 0) // If the block is the most to the right
		{
			int32 Random = FMath::RandRange(1, 2); // Go to the left or up
			if(Random == 1) // Go to the left
			{
				if(!bWalkableArray[BlockCounter-1]) // If left isn't already selected go left
				{
					BlockCounter -= 1;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
				else // If left is selected, go up
				{
					BlockCounter += 5;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
			}
			else // Go up
			{
				BlockCounter += 5;
				BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
				BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
				bWalkableArray[BlockCounter] = true;
			}
		}
		else // The block is inbetween two
		{
			int32 Random = FMath::RandRange(1, 3); // Go right, left or up
			if(Random == 1) // Go to the right
			{
				if(!bWalkableArray[BlockCounter+1]) // If right isn't already selected go right
				{
					BlockCounter += 1;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
				else // If right is selected, go up
				{
					BlockCounter += 5;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
			}
			else if(Random == 2) // Go to the left
			{
				if(!bWalkableArray[BlockCounter-1]) // If left isn't already selected go left
				{
					BlockCounter -= 1;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
				else // If left is selected, go up
				{
					BlockCounter += 5;
					BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
					BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
					bWalkableArray[BlockCounter] = true;
				}
			}
			else // Go up
			{
				BlockCounter += 5;
				BlockArray[BlockCounter]->SetMaterial(2, PassMaterial);
				BlockArray[BlockCounter]->SetCollisionProfileName(FName("BlockAllDynamic"));
				bWalkableArray[BlockCounter] = true;
			}
		}
	}

}

// Function to spawn new ingredient into the machine to be picked up
void AAObstacle38::SpawnIngredient()
{
	if(DunkedIngredients >= NumIngredients) // Check if the obstacle isn't finished
	{
		return;
	}
	// Spawn ingredient and save in variable LastIngredient
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	if(IngredientClassRef)
	{
		LastIngredient = GetWorld()->SpawnActor<AAIngredient>(IngredientClassRef, IngredientSpawnCollision->GetComponentTransform(), SpawnParameters);
		
		LastIngredient->AttachToComponent(IngredientSpawnCollision, AttachmentRules);
	}
}

// Function to be called on BlockCollision begin overlap to disable jump
void AAObstacle38::OnBlockCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == PlayerRef)
	{
		PlayerRef->CC_SetJump(false);
	}
}

// Function to be called on BlockCollision end overlap to enable jump
void AAObstacle38::OnBlockCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == PlayerRef)
	{
		PlayerRef->CC_SetJump(true);
	}
}
