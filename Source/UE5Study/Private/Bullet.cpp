// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "../UE5Study.h"
#include "ShootingGameModeBase.h"
#include "Enemy.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(CollisionComponent);
	StaticMeshComponent->SetupAttachment(CollisionComponent);

	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->SetCollisionProfileName(TEXT("Bullet"));
	//CollisionComponent->SetCollisionObjectType(ECC_Bullet);
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//CollisionComponent->SetCollisionResponseToChannel(ECC_Enemy, ECollisionResponse::ECR_Overlap);
	//CollisionComponent->SetCollisionResponseToChannel(ECC_KillZone, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletBeginOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (MoveSpeed * DeltaTime) * GetActorForwardVector());
}

void ABullet::OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	if (enemy != nullptr)
	{
		enemy->Destroy();
		AShootingGameModeBase* GameMode = Cast<AShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode != nullptr)
		{
			GameMode->AddScore(1);
		}
	}

    Destroy();
}
