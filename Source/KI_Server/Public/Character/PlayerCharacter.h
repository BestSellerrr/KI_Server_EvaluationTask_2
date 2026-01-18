// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class KI_SERVER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Update_Score(int32 Score);

	UFUNCTION(Server, Reliable)
	void Server_Update_Score(int32 Score);

};
