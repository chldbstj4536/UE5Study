// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UE5StudyPrecompiled.h"
#include "EnemyFactory.generated.h"

UCLASS()
class UE5STUDY_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> EnemySubclass;
	UPROPERTY(EditAnywhere)
	float SpawnTime;

private:
	float CurrentSpawnTime = 0.0f;
};
