// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawner.h"
#include "Ball.h"
#include "Kismet/GameplayStatics.h"
#include "PlatePawn.h"

// Sets default values
ABallSpawner::ABallSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	APlatePawn* PlatePawn = Cast<APlatePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlatePawn)
	{
		PlatePawn->OnSpawnAnotherBall.AddDynamic(this, &ABallSpawner::SpawnBall);
	}

}

// Called every frame
void ABallSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Получить рандомное место спауна
FVector ABallSpawner::GetRandomLocationToSpawn()
{
	FVector VectorToReturn = this->GetActorLocation();
	VectorToReturn += FVector(FMath::RandRange(-650, 650), FMath::RandRange(-650, 650), -50);
	return VectorToReturn;
}

//Спаун шарика
void ABallSpawner::SpawnBall()
{

	FActorSpawnParameters TempSpawnParams;
	FTransform BallToSpawnTransform;
	BallToSpawnTransform.SetLocation(GetRandomLocationToSpawn());


	ABall* BallActor = Cast<ABall>(GetWorld()->SpawnActor(BallToSpawn, &BallToSpawnTransform, TempSpawnParams));
	if (BallActor)
	{
		BallActor->BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BallActor->BallMesh->SetSimulatePhysics(true);

	}

}
