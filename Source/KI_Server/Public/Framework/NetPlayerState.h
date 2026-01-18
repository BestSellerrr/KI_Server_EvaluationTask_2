// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KI_SERVER_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Point();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Point)
	int32 Point = 0;

private:
	TWeakObjectPtr<class UNetHUDWidget> NetHUDWidget = nullptr;
};
