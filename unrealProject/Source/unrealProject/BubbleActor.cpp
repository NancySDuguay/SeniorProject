// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealProject.h"
#include "BubbleActor.h"
#include "unrealProjectCharacter.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel2

// Sets default values
ABubbleActor::ABubbleActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ColComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &ABubbleActor::OnHit);

	RootComponent = CollisionComp;

	EnemyMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->AttachTo(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABubbleActor::BeginPlay()
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

	MoveX = 1190.0;
	MoveY = 1000.0;
	MoveZ = 352.0;

	FVector mover(MoveX, MoveY, MoveZ);
	this->SetActorLocation(mover, true);
	savepoint = this->GetActorLocation();



	MoveX = savepoint.X;
	MoveY = savepoint.Y;
	MoveZ = savepoint.Z;

	startLoc = FVector(savepoint.X, savepoint.Y, savepoint.Z);
	
}

// Called every frame
void ABubbleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	savepoint = this->GetActorLocation();

	MoveX = savepoint.X;
	MoveY = savepoint.Y;
	MoveZ = savepoint.Z;

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

		//MoveZ += 100.0f * DeltaTime;
		MoveZ += 2;
		//UE_LOG(LogTemp, Warning, TEXT("X %f"), this->MoveZ);
		FVector mover(MoveX, MoveY, MoveZ);
		this->SetActorLocation(mover, true);

		if ((MoveZ > 11630) && (MoveZ <= 11632))
		{
			//GetWorld()->SpawnActor(ABubbleActor::StaticClass());
			GetWorld()->SpawnActor<ABubbleActor>(GetClass(), startLoc, FRotator::ZeroRotator);
		}
		else if (MoveZ > 12010)
		{
			Destroy();
		}
	}

}

/*void ABubbleActor::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}*/

void ABubbleActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("X %f"), this->Scale);
	//Destroy();
	if (OtherActor->IsA(AunrealProjectCharacter::StaticClass()))
	{
		//World->SpawnActor<
		/*health--;

		if (health <= 0)
		{
		Destroy();
		}*/
		//ABubble::StaticClass()->GetDefaultObject();

		//GetWorld()->SpawnActor<ABubble>(SpawnLocation, FireRotation);

		//GetWorld()->SpawnActor(ABubble::StaticClass());
		//Destroy();

		//FVector moveAct(MoveX, MoveY, MoveZ+3);
		//OtherActor->SetActorLocation(moveAct, true);

		//OtherActor->SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//OtherActor->AttachRootComponentTo(CollisionComp);

		//FString please = OtherActor->GetName();

		//OtherActor->GetClass()->GetName();
		OtherActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("NAME %s"), *OtherActor->GetClass()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("NAME %s"), please);

		if (OtherActor->GetClass()->GetName() == "SideScrollerCharacter2_C")
		{
			GetWorld()->SpawnActor<ABubbleActor>(GetClass(), startLoc, FRotator::ZeroRotator);
			//GetWorld()->SpawnActor(ABubbleActor::StaticClass());
			Destroy();
			UE_LOG(LogTemp, Warning, TEXT("YAAAAAAS"))
		}
	}

}
