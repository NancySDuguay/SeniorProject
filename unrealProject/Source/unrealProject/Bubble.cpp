// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealProject.h"
#include "Bubble.h"
#include "unrealProjectCharacter.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel2
// Sets default values
ABubble::ABubble(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{


	//ColComp = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ColComp"));
	//RootComponent = ColComp;



	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ColComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &ABubble::OnHit);

	RootComponent = CollisionComp;

	EnemyMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->AttachTo(RootComponent);



	//ObjectComponent = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("object"));
	//ObjectComponent->AttachTo(RootComponent);

	//CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollComp"));
	//CollisionComp->OnComponentHit.AddDynamic(this, &Aenemy::OnHit);

	//rotSpeed = 100.0f;
	//scale = 0.5;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABubble::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");

	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);


	MoveX = 1190.0;
	MoveY = 800.0;
	MoveZ = 352.0;

	FVector mover(MoveX, MoveY, MoveZ);
	this->SetActorLocation(mover, true);
	//savepoint = this->GetActorLocation();



	//MoveX = savepoint.X;
	//MoveY = savepoint.Y;
	//MoveZ = savepoint.Z;
	
}

// Called every frame
void ABubble::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (Scale <= 1.5)
	{
		Scale += 2.0f * DeltaTime;
		//RotRoll += rotSpeed * DeltaTime;

		//UE_LOG(LogTemp, Warning, TEXT("X %f"), this->MoveX);
		//UE_LOG(LogTemp, Warning, TEXT("JUST DO IT %f"), this->MoveY);

		FVector scaler(Scale, Scale, Scale);
		//FRotator rotate(RotPitch, RotYaw, RotRoll);

		CollisionComp->SetWorldScale3D(scaler);
		//ObjectComponent->SetRelativeRotation(rotate, true);
	}
	else 
	{
		MoveZ += 100.0f * DeltaTime;
		FVector mover(MoveX, MoveY, MoveZ);
		this->SetActorLocation(mover, true);
	}

	
}

// Called to bind functionality to input
void ABubble::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABubble::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("X %f"), this->Scale);
	//Destroy();
	if (OtherActor->IsA(AunrealProjectCharacter::StaticClass()))
	{
		/*health--;

		if (health <= 0)
		{
			Destroy();
		}*/
		//ABubble::StaticClass()->GetDefaultObject();
		GetWorld()->SpawnActor(ABubble::StaticClass());
		//GetWorld()->SpawnActor<ABubble>(SpawnLocation, FireRotation);
		Destroy();
		
	}

}