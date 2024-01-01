// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ATimeManager::ATimeManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LastFunctionCallTime = FPlatformTime::Seconds();

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	
	//spawnTimer = 0.0f;
	gameTimer = 0.0f;

	//gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));


}




void ATimeManager::UpdateTimeManager(float DeltaTime)
{

	deltaTime = DeltaTime;
	//spawnTimer += GetWorld()->GetDeltaSeconds();
	gameTimer += GetWorld()->GetDeltaSeconds();


	double CurrentTime = FPlatformTime::Seconds();
	double DeltaTimeInSeconds = CurrentTime - LastFunctionCallTime;

	// Use DeltaTimeInSeconds and display it
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, // Key, -1 means we don't overwrite previous messages
			5.0f, // Time to display the message (5 seconds)
			FColor::Green, // The color of the text
			FString::Printf(TEXT("Delta Time: %f seconds"), DeltaTimeInSeconds)
		);
	}

	LastFunctionCallTime = CurrentTime;
}




void ATimeManager::IncrementTime(float* time)
{


	*time += deltaTime;

}