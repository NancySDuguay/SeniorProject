// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BellFlowerFall.generated.h"

UCLASS()
class UNREALPROJECT_API ABellFlowerFall : public APawn
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(Category = Move, EditAnywhere, BlueprintReadWrite)
		float rotSpeed;

	float MoveX;
	float MoveY;
	float MoveZ;

	float RotPitch;
	float RotYaw;
	float RotRoll;

	float Scale;

	FVector savepoint;
	FVector mover;

public:

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* EnemyMesh;

	// Sets default values for this pawn's properties
	//ABellFlowerFall();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	bool isFall;

};