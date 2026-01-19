// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h" 

APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


