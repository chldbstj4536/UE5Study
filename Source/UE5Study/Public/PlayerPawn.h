// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UE5StudyPrecompiled.h"
#include "PlayerPawn.generated.h"

UCLASS()
class UE5STUDY_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveHorizontal(float value);
	void MoveVertical(float value);
	void Fire();

	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
    class UArrowComponent* ArrowComponent;
	UPROPERTY(EditAnywhere)
	class USoundBase* FireFXSound;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 500.0f;
	UPROPERTY(VisibleAnywhere)
	FVector Direction;
	UPROPERTY(EditAnywhere)
    TSubclassOf<class ABullet> Bullet;
};
