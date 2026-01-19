// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetPlayerState.h"
#include "Framework/NetHUD.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "UI/NetHUDWidget.h"

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, Point);
}

void ANetPlayerState::OnRep_Point()
{
	if (!NetHUDWidget.IsValid())
	{
		APlayerController* LocalPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!LocalPC)
			return;
		ANetHUD* HUD = LocalPC->GetHUD<ANetHUD>();
		if (!HUD || !(HUD->GetNetHUDWidget().IsValid()))
			return;
		NetHUDWidget = Cast<UNetHUDWidget>(HUD->GetNetHUDWidget().Get());
	}

	if (NetHUDWidget.IsValid())
	{
		bool bIsLocalPlayer = false;
		APlayerController* LocalPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (LocalPC->PlayerState == this)
		{
			bIsLocalPlayer = true;
		}

		NetHUDWidget->UpdatePoint(Point, bIsLocalPlayer);
	}
}

void ANetPlayerState::AddPoint()
{
	if (HasAuthority())
	{
		Point++;
		OnRep_Point();
	}
}
