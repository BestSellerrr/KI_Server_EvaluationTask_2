// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANetGameState::BeginPlay()
{
	GamePlayTime = 60.0f;
}

void ANetGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (GamePlayTime >= 0.0f && !bFinish)
		{
			GamePlayTime -= DeltaTime;	
		}
		else
		{
			GamePlayTime = 0.0f;
			bFinish = true;
		}
	}
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, GamePlayTime);
	DOREPLIFETIME(ANetGameState, bFinish);
}
