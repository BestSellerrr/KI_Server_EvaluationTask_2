// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NetPointActorSpawner.h"

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

	TimerDelegate.BindUObject(this, &ANetPointActorSpawner::RandomSpawn);
	World->GetTimerManager().SetTimer(
		SpawnActorTimer,
		TimerDelegate,
		3.0f,
		true
	);

	// 스폰액터 만들고 난 후 테스트 안함(확인 필요)
}

void ANetPointActorSpawner::RandomSpawn()
{
	UE_LOG(LogTemp, Log, TEXT("ActorSpawn"));
	UWorld* World = GetWorld();
	if (!World)
		return;
	if (!SpawnActor)
		return;

	float X = FMath::FRandRange(-SpawnRange, SpawnRange);
	float Y = FMath::FRandRange(-SpawnRange, SpawnRange);
	FVector RandomVector = FVector(X, Y, 0);

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	World->SpawnActor<AActor>(
		SpawnActor,
		RandomVector,
		GetActorRotation(),
		Params
	);

	return;
}

