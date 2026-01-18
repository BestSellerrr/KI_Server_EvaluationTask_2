// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{

}

void ANetGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (GamePlayTime >= 0.0f && !IsFinish)
		{
			GamePlayTime -= DeltaTime;	
			IsFinish = true;
		}
		else
		{
			GamePlayTime = 0.0f;
		}
	}
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, GamePlayTime);
}
