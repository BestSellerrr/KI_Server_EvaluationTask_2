// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NetHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class KI_SERVER_API UNetHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateTime();

public:
	void UpdatePoint(int32 Point, bool bIsLocal);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	TObjectPtr<class UTextBlock> PlayerPoint = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	TObjectPtr<class UTextBlock> EnemyPoint = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget));
	TObjectPtr<class UTextBlock> GameTimer = nullptr;

private:
	TWeakObjectPtr<class ANetGameState> CachedNetGameState = nullptr;
};
