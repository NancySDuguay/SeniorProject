// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealProject.h"
#include "FlowerGrow.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel2
// Sets default values
AFlowerGrow::AFlowerGrow(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ColComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &AFlowerGrow::OnHit);

	RootComponent = CollisionComp;

	EnemyMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->AttachTo(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlowerGrow::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");

	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	//MoveX = 1190.0;
	//MoveY = 1000.0;
	//MoveZ = 352.0;

	//FVector mover(MoveX, MoveY, MoveZ);
	//this->SetActorLocation(mover, true);
	savepoint = this->GetActorLocation();



	MoveX = savepoint.X;
	MoveY = savepoint.Y;
	MoveZ = savepoint.Z;
	
}

// Called every frame
void AFlowerGrow::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("Y %f"), this->MoveY);

}

void AFlowerGrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("X %f"), this->MoveX);
	//UE_LOG(LogTemp, Warning, TEXT("X %f"), this->Scale);
	//Destroy();
	/*if (OtherActor->IsA(AunrealProjectCharacter::StaticClass()))
	{
		OtherActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("NAME %s"), *OtherActor->GetClass()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("NAME %s"), please);

		if (OtherActor->GetClass()->GetName() == "SideScrollerCharacter2_C")
		{
			Destroy();
			UE_LOG(LogTemp, Warning, TEXT("YAAAAAAS"))
		}
	}*/

}