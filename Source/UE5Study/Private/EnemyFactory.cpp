// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "EnemyFactory.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSpawnTime += DeltaTime;
	if (CurrentSpawnTime >= SpawnTime)
	{
		CurrentSpawnTime -= SpawnTime;
		GetWorld()->SpawnActor<AEnemy>(EnemySubclass, GetActorLocation(), GetActorRotation());
	}
}

