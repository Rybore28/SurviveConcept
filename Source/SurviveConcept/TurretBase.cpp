// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretBase.h"
#include "CanonProjectile.h"

// Sets default values
ATurretBase::ATurretBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	Mesh1P = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh2P = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MESH2"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	RootComponent = CollisionBox;
	CollisionBox->bVisible = true;
	CollisionBox->bHiddenInGame = true;
	Mesh1P->SetupAttachment(RootComponent, NAME_None);
}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretBase::Fire_Implementation()
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ACanonProjectile>(ProjectileClass, GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
}
// Called to bind functionality to input
void ATurretBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATurretBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATurretBase::LookUpAtRate);
}
void ATurretBase::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATurretBase::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
