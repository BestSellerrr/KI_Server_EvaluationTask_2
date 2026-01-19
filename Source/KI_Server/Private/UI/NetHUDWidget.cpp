// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NetHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/NetGameState.h"
#include "Components/TextBlock.h"

void UNetHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WinTextBlock)
	{
		WinTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	if (LoseTextBlock)
	{
		LoseTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UNetHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedNetGameState.IsValid())
	{
		CachedNetGameState = Cast<ANetGameState>(UGameplayStatics::GetGameState(this));
		if (CachedNetGameState.IsValid())
		{
			CachedNetGameState->OnGameOver.BindUObject(this, &UNetHUDWidget::UpdateGameOverDisplay);
		}
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
		CachedPlayerPoint = Point;
		PlayerPoint->SetText(FText::FromString(FString::Printf(TEXT("Player : %d"), Point)));
	}
	else
	{
		CachedEnemyPoint = Point;
		EnemyPoint->SetText(FText::FromString(FString::Printf(TEXT("Enemy : %d"), Point)));
	}
}

void UNetHUDWidget::UpdateGameOverDisplay()
{
	UE_LOG(LogTemp, Log, TEXT("GameOver"));

	if (!CachedNetGameState.IsValid())
		return;
	if (!WinTextBlock || !LoseTextBlock)
		return;
	
	if (CachedPlayerPoint > CachedEnemyPoint)
	{
		WinTextBlock->SetVisibility(ESlateVisibility::Visible);
		LoseTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (CachedPlayerPoint < CachedEnemyPoint)
	{
		LoseTextBlock->SetVisibility(ESlateVisibility::Visible);
		WinTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		WinTextBlock->SetText(FText::FromString(TEXT("Draw")));
		WinTextBlock->SetVisibility(ESlateVisibility::Visible);
		LoseTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

	CachedNetGameState->OnGameOver.Unbind();
}
