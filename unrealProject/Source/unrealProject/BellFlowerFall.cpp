// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealProject.h"
#include "BellFlowerFall.h"
#include "unrealProjectCharacter.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel2

// Sets default values
ABellFlowerFall::ABellFlowerFall(const FObjectInitializer& ObjectInitializer)
{

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ColComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &ABellFlowerFall::OnHit);

	RootComponent = CollisionComp;

	EnemyMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->AttachTo(RootComponent);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABellFlowerFall::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");

	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);


	//MoveX = 1190.0;
	//MoveY = 800.0;
	//MoveZ = 352.0;

	//FVector mover(MoveX, MoveY, MoveZ);
	//this->SetActorLocation(mover, true);
	savepoint = this->GetActorLocation();

	isFall = false;

	MoveX = savepoint.X;
	MoveY = savepoint.Y;
	MoveZ = savepoint.Z;

	rotSpeed = 100.0f;

}

// Called every frame
void ABellFlowerFall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFall == true)
	{
		MoveZ -= 100.0f * DeltaTime;
		FVector mover(MoveX, MoveY, MoveZ);
		this->SetActorLocation(mover, true);

		RotYaw += rotSpeed * DeltaTime;
		FRotator rotate(RotPitch, RotYaw, RotRoll);
		CollisionComp->SetRelativeRotation(rotate, true);
	}

}

// Called to bind functionality to input
void ABellFlowerFall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABellFlowerFall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
		//GetWorld()->SpawnActor<ABubble>(SpawnLocation, FireRotation);


		//GetWorld()->SpawnActor(ABubble::StaticClass());
		//Destroy();
		isFall = true;

	}
}
