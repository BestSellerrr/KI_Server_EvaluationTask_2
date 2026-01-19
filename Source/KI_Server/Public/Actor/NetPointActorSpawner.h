// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetPointActorSpawner.generated.h"

UCLASS()
class KI_SERVER_API ANetPointActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ANetPointActorSpawner();

protected:
	virtual void BeginPlay() override;

	void RandomSpawn();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<AActor> SpawnActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	float SpawnRange = 1000.0f;

private:
	FTimerHandle SpawnActorTimer;
	FTimerDelegate TimerDelegate;
};
