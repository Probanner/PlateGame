// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Инициализация компонентов шарика
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	RootComponent = BallMesh;
	BallMesh->OnComponentHit.AddDynamic(this,&ABall::OnCompHit);


}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Утяжеление шарика при попадании на платформу
void ABall::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BallMesh->SetMassOverrideInKg("1000");
	BallMesh->SetLinearDamping(20);
}

//Киллзона
void ABall::onDeath()
{
	if (DeathSounds.Num() != 0 && !IsDestroyedByCenter)
	{
		int32 RandomIndex = FMath::RandRange(0, DeathSounds.Num() - 1);
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, DeathSounds[RandomIndex], 1);
	}
	this->Destroy();
}

//Середина
void ABall::onPlusScore()
{
	IsDestroyedByCenter = true;
	if (GroovySounds.Num() != 0)
	{
		int32 RandomIndex = FMath::RandRange(0, GroovySounds.Num() - 1);
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, GroovySounds[RandomIndex], 1);
	}
	this->Destroy();
}

