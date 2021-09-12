// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"


UCLASS()
class TASK_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
	class UStaticMeshComponent* BallMesh = nullptr;

	//Массивы для звуков
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroovySounds")
		TArray<USoundBase*> GroovySounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GroovySounds")
		TArray<USoundBase*> DeathSounds;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

		void onDeath();
		void onPlusScore();
		bool IsDestroyedByCenter = false;
};
