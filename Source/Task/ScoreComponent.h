// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ball.h"
#include "ScoreComponent.generated.h"


//Компонент счета. Также ресает новые шарики

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChange,float,DelegateScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TASK_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
		TSubclassOf<class ABall> BallToSpawn = nullptr;

	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Score")
	FOnScoreChange OnScoreChange;

	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Score")
	FOnDead OnDead;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float Score = 5.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector GetRandomLocationToSpawn(FVector _Hight);

	UFUNCTION(BlueprintCallable)
	void SpawnBall(FVector _BallLocation);

	UFUNCTION(BlueprintCallable) 
	void SetScore(float _newScore);

	UFUNCTION(BlueprintCallable)
	float GetScore();


};
