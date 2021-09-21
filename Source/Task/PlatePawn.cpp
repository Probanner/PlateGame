// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatePawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APlatePawn::APlatePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Инициализация компонентов пауна

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>("Plate Mesh");
	PlateMesh->SetupAttachment(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	ScoreComponent = CreateDefaultSubobject<UScoreComponent>("ScoreComponent");

	PlusPointZone = CreateDefaultSubobject<UBoxComponent>("Plus Point Zone");
	PlusPointZone->SetupAttachment(SceneComponent);
	
	if (PlusPointZone)
	{
		PlusPointZone->OnComponentBeginOverlap.AddDynamic(this, &APlatePawn::PlusScoreOverlap);
	}

	KillZone = CreateDefaultSubobject<UBoxComponent>("Kill Zone");

	if (KillZone)
	{
		KillZone->OnComponentEndOverlap.AddDynamic(this, &APlatePawn::KillBoxOverlap);
	}


}

// Called when the game starts or when spawned
void APlatePawn::BeginPlay()
{
	Super::BeginPlay();
	OnSpawnAnotherBall.Broadcast();
}

// Called every frame
void APlatePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlatePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Поворот вперед/назад
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlatePawn::InputAxisX);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlatePawn::InputAxisY);
	// Reset поворота платформы
	PlayerInputComponent->BindAction(TEXT("ResetRotate"), IE_Pressed, this, &APlatePawn::ResetRotate);
}


void APlatePawn::InputAxisX(float InputX)
{	
	if ((SceneComponent->GetRelativeRotation().Pitch < 25 && InputX>0) 
	|| (SceneComponent->GetRelativeRotation().Pitch > -25 && InputX < 0))
	{	
		float DeltaTime = FApp::GetDeltaTime();
		FRotator RotateTemp(InputX * DeltaTime * 100, 0, 0);
		SceneComponent->AddRelativeRotation(RotateTemp.Quaternion());
	}
}
	

void APlatePawn::InputAxisY(float InputY)
{
	if ((SceneComponent->GetRelativeRotation().Roll < 25 && InputY>0)
		|| (SceneComponent->GetRelativeRotation().Roll > -25 && InputY < 0))
	{
		float DeltaTime = FApp::GetDeltaTime();
		FRotator RotateTemp(0, 0, InputY * DeltaTime * 100);
		SceneComponent->AddRelativeRotation(RotateTemp.Quaternion());
	}
}

//BeginOverlap на середину платформы
void APlatePawn::PlusScoreOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	
	ABall* BallActor = Cast<ABall>(OtherActor);
	if (BallActor)
	{
		ScoreComponent->SetScore(PlusPointValue+(-MinusPointValue));
		BallActor->onPlusScore();

		//Световой эффект при попадании в середину
		if (myParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), myParticleSystem,
				FTransform(SceneComponent->GetRelativeRotation(),
					SceneComponent->GetRelativeLocation(), FVector(1.0f)));
		}
	}

}

//EndOverlap на вылет шарика
void APlatePawn::KillBoxOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ABall* BallActor = Cast<ABall>(OtherActor);

	if (BallActor)
	{
		BallActor->onDeath();
		ScoreComponent->SetScore(MinusPointValue);
		if (ScoreComponent->GetScore() >= 0)
		{
			//ScoreComponent->SpawnBall(CameraBoom->GetRelativeLocation());
			OnSpawnAnotherBall.Broadcast();
		}
		
	}
	
}

//Обнуление поворота платформы
void APlatePawn::ResetRotate()
{
	//Отключение инпутов для безшовного поворота
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	DisableInput(PlayerController);

	//Плавное обнуление поворота
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &APlatePawn::ResetRotateTick, 0.005, true);
	
}

void APlatePawn::ResetRotateTick()
{

	SceneComponent->SetRelativeRotation(FMath::RInterpTo(SceneComponent->GetRelativeRotation(),
	FRotator(0,0,0),GetWorld()->DeltaTimeSeconds,15));

	if (SceneComponent->GetRelativeRotation().IsNearlyZero(0.5f))
	{
		GetWorldTimerManager().ClearTimer(FuzeTimerHandle);

		//Включение инпутов
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		EnableInput(PlayerController);

	}
}

