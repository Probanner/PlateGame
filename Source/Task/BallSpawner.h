// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallSpawner.generated.h"

UCLASS()
class TASK_API ABallSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
		TSubclassOf<class ABall> BallToSpawn = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	FVector GetRandomLocationToSpawn();

	UFUNCTION(BlueprintCallable)
		void SpawnBall();


};
