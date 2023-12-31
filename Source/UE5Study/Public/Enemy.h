// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UE5StudyPrecompiled.h"
#include "Enemy.generated.h"

UCLASS()
class UE5STUDY_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 800.0f;
	UPROPERTY(EditAnywhere)
	FVector Direction;
	UPROPERTY(EditAnywhere)
	float TraceRate = 0.5f;
	UPROPERTY(EditAnywhere)
	class USoundBase* DestroySoundFX;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplosionFX;
};
