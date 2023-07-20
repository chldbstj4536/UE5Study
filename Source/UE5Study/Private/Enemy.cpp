// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "../UE5Study.h"
#include "ShootingGameModeBase.h"
#include "PlayerPawn.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(CollisionComponent);
	StaticMeshComponent->SetupAttachment(CollisionComponent);

	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->SetCollisionProfileName(TEXT("Enemy"));
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComponent->SetCollisionObjectType(ECC_Enemy);
	//CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//CollisionComponent->SetCollisionResponseToChannel(ECC_Player, ECollisionResponse::ECR_Overlap);
	//CollisionComponent->SetCollisionResponseToChannel(ECC_Bullet, ECollisionResponse::ECR_Overlap);
	//CollisionComponent->SetCollisionResponseToChannel(ECC_KillZone, ECollisionResponse::ECR_Overlap);
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

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
}
void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySound2D(GetWorld(), DestroySoundFX);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (MoveSpeed * DeltaTime) * Direction);
}

void AEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	
	if (player != nullptr)
	{
		player->Destroy();
		Cast<AShootingGameModeBase>(GetWorld()->GetAuthGameMode())->GameOver();
	}

	Destroy();
}
