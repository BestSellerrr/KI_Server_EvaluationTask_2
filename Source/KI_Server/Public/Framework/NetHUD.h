// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NetHUD.generated.h"

/**
 * 
 */
UCLASS()
class KI_SERVER_API ANetHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	inline TWeakObjectPtr<UUserWidget> GetNetHUDWidget() { return NetHUDWidget; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> NetHUDWidgetClass = nullptr;

private:
	TWeakObjectPtr<UUserWidget> NetHUDWidget = nullptr;

};
