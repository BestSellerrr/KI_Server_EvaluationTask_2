// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NetHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/NetGameState.h"
#include "Components/TextBlock.h"

void UNetHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedNetGameState.IsValid())
	{
		CachedNetGameState = Cast<ANetGameState>(UGameplayStatics::GetGameState(this));
	}

	UpdateTime();
}

void UNetHUDWidget::UpdateTime()
{
	if (!GameTimer)
		return;

	int32 Time = FMath::FloorToInt(CachedNetGameState->GetGameplayTime());
	int32 Minutes = Time / 60;
	int32 Seconds = Time % 60;

	GameTimer->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
}

void UNetHUDWidget::UpdatePoint(int32 Point, bool bIsLocal)
{
	if (!PlayerPoint || !EnemyPoint)
		return;

	if (bIsLocal)
	{
		PlayerPoint->SetText(FText::FromString(FString::Printf(TEXT("Player : %d"), Point)));
	}
	else
	{
		EnemyPoint->SetText(FText::FromString(FString::Printf(TEXT("Enemy : %d"), Point)));
	}
}
