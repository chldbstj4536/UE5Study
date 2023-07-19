// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "../UE5Study.h"
#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("FireDirection"));

	SetRootComponent(CollisionComponent);
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	ArrowComponent->SetupAttachment(CollisionComponent);

	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->SetCollisionProfileName(TEXT("Player"));
	//CollisionComponent->SetCollisionObjectType(ECC_Player);
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	//CollisionComponent->SetCollisionResponseToChannel(ECC_Enemy, ECR_Overlap);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SetActorLocation(GetActorLocation() + (MoveSpeed * DeltaTime * Direction));
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawn::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawn::MoveVertical);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayerPawn::Fire);
}

void APlayerPawn::MoveHorizontal(float value)
{
	Direction.Y = value;
	Direction.Normalize();
}

void APlayerPawn::MoveVertical(float value)
{
	Direction.Z = value;
	Direction.Normalize();
}

void APlayerPawn::Fire()
{
	FTransform FireTransform = ArrowComponent->GetComponentTransform();

	UE_LOG(LogTemp, Warning, TEXT("Fire"));

	GetWorld()->SpawnActor<ABullet>(Bullet, ArrowComponent->GetComponentLocation(), ArrowComponent->GetComponentRotation());
	UGameplayStatics::PlaySound2D(GetWorld(), FireFXSound);
}
