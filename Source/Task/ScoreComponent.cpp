// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreComponent.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();


	
}


// Called every frame
void UScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Рандомные координаты спауна шарика
FVector UScoreComponent::GetRandomLocationToSpawn(FVector _CameraVector)
{
	_CameraVector += FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), -50);
	return _CameraVector;
}

//Спаун шарика
void UScoreComponent::SpawnBall(FVector _CameraLocation)
{

	FActorSpawnParameters TempSpawnParams;
	FTransform BallToSpawnTransform;
	BallToSpawnTransform.SetLocation(GetRandomLocationToSpawn(_CameraLocation));


	ABall* BallActor = Cast<ABall>(GetWorld()->SpawnActor(BallToSpawn, &BallToSpawnTransform, TempSpawnParams));
	if (BallActor)
	{
		BallActor->BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BallActor->BallMesh->SetSimulatePhysics(true);
	
	}
	
}

//Изменение счета
void UScoreComponent::SetScore(float _newScore)
{
	Score += _newScore;
	if (Score<0)
	{
		OnDead.Broadcast();
	}
	OnScoreChange.Broadcast(Score);
}

//Получение счета
float UScoreComponent::GetScore()
{
	return Score;
}

