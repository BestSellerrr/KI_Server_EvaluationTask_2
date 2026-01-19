// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetHUD.h"
#include "Blueprint/UserWidget.h"

void ANetHUD::BeginPlay()
{
	Super::BeginPlay();

	if (NetHUDWidgetClass)
	{
		NetHUDWidget = CreateWidget<UUserWidget>(GetWorld(), NetHUDWidgetClass);
		if (NetHUDWidget.IsValid())
		{
			NetHUDWidget->AddToViewport();
		}
	}
}
