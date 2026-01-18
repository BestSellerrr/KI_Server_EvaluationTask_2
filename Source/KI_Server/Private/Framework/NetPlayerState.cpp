// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "UI/NetHUDWidget.h"

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(ANetPlayerState, Point);
}

void ANetPlayerState::OnRep_Point()
{
	if (!NetHUDWidget.IsValid())
	{
		if (!GetPlayerController())
			return;
		// HUD 생성 후 HUD확인, HUD의 위젯 확인, 
	}

	if (NetHUDWidget.IsValid())
	{
		NetHUDWidget->UpdatePoint();	// NetHUDWidget에 구현 필요
	}
}
