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

//��������� �����
void UScoreComponent::SetScore(float _newScore)
{
	Score += _newScore;
	if (Score<0)
	{
		OnDead.Broadcast();
	}
	OnScoreChange.Broadcast(Score);
}

//��������� �����
float UScoreComponent::GetScore()
{
	return Score;
}

