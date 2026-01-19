// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NetPointActorSpawner.h"
#include "Framework/NetGameState.h"

// Sets default values
ANetPointActorSpawner::ANetPointActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANetPointActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HasAuthority())
		return;
	UWorld* World = GetWorld();
	if (!World)
		return;
	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ANetGameState>(World->GetGameState());
	}

	TimerDelegate.BindUObject(this, &ANetPointActorSpawner::RandomSpawn);
	World->GetTimerManager().SetTimer(
		SpawnActorTimer,
		TimerDelegate,
		3.0f,
		true,
		0.0f
	);
}

void ANetPointActorSpawner::RandomSpawn()
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	if (!SpawnActor)
		return;

	float X = FMath::FRandRange(-SpawnRange, SpawnRange);
	float Y = FMath::FRandRange(-SpawnRange, SpawnRange);
	FVector RandomVector = GetActorLocation() + FVector(X, Y, 0);

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	World->SpawnActor<AActor>(
		SpawnActor,
		RandomVector,
		GetActorRotation(),
		Params
	);

	if (CachedGameState->GetbFinish())
	{
		World->GetTimerManager().ClearTimer(SpawnActorTimer);
		return;
	}

	return;
}

