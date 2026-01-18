// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

/**
 * 
 */
UCLASS()
class KI_SERVER_API ANetGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ANetGameState();

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	inline float GetGameplayTime() { return GamePlayTime; }

protected:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Game|Data")
	float GamePlayTime = 60.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game|Data")
	bool IsFinish = false;
};
