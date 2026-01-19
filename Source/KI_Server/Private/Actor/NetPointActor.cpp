// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NetPointActor.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Framework/NetPlayerState.h"

// Sets default values
ANetPointActor::ANetPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SetRootComponent(Arrow);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Arrow);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Arrow);
}

// Called when the game starts or when spawned
void ANetPointActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ANetPointActor::OnBeginOverlap);
}

void ANetPointActor::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (!Character)
		{
			UE_LOG(LogTemp, Log, TEXT("OtherActor가 Character가 아닙니다"))
				return;
		}
		ANetPlayerState* PS = Cast<ANetPlayerState>(Character->GetPlayerState());
		if (!PS)
		{
			UE_LOG(LogTemp, Log, TEXT("OtherActor의 NetPlayerState가 없습니다"));
			return;
		}

		PS->AddPoint();
		Destroy();
	}
}

