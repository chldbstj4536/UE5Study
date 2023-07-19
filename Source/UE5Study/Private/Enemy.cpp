// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(CollisionComponent);
	StaticMeshComponent->SetupAttachment(CollisionComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (FMath::FRandRange(0.0, 1.0) <= TraceRate)
	{
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			Direction = player->GetActorLocation() - GetActorLocation();
			Direction.Normalize();
		}
	}
	else
	{
		Direction = GetActorForwardVector();
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (MoveSpeed * DeltaTime) * Direction);
}
