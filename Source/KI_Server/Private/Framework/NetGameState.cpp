// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANetGameState::BeginPlay()
{
	Super::BeginPlay();

	bFinish = false;
}

void ANetGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (GamePlayTime > 0.0f)
		{
			GamePlayTime -= DeltaTime;	
		}
		else
		{
			GamePlayTime = 0.0f;
			bFinish = true;
		}
	}
	if (bFinish)
	{
		OnGameOver.ExecuteIfBound();
	}
	
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, GamePlayTime);
	DOREPLIFETIME(ANetGameState, bFinish);
}
