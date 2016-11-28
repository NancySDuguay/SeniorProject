// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealProject.h"
//#include "coltest.h"
#include "enemy.h"

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel1
#define COLLISION_ALLIE ECollisionChannel::ECC_GameTraceChannel2

// Sets default values
Aenemy::Aenemy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ColComp"));
	CollisionComp->OnComponentHit.AddDynamic(this, &Aenemy::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLIE, ECollisionResponse::ECR_Block);

	RootComponent = CollisionComp;

	EnemyMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->AttachTo(RootComponent);

	health = 10;
}

// Called when the game starts or when spawned
void Aenemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aenemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void Aenemy::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor->IsA(AcoltestProjectile::StaticClass()))
	//{
		health--;

		if (health <= 0)
		{
			Destroy();
		}
	//}

}

