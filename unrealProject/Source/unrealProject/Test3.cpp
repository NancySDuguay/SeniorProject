// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealProject.h"
#include "Test3.h"


// Sets default values
ATest3::ATest3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest3::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest3::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

