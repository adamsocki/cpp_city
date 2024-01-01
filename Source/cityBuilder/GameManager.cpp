// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "cityBuilderPlayerController.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

////////
//	GAME START

////////


// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	PrimaryActorTick.TickInterval = 0.001f;
	Super::BeginPlay();

	GameData = {};
	GameData.em = {};

	GameData.em.entities = {};

	controllerState = EControllerState::ControllerState_GamePlay;



	timeManager = Cast<ATimeManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass()));
	resourceManager = Cast<AResourceManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AResourceManager::StaticClass()));
	buildingManager = Cast<AbuildingManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AbuildingManager::StaticClass()));
	residentManager = Cast<AResidentManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AResidentManager::StaticClass()));
	uiManager = Cast<AUIManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AUIManager::StaticClass()));
	//myEntityManager = Cast<AMyEntityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyEntityManager::StaticClass()));
	unitManager = Cast<AUnitManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AUnitManager::StaticClass()));

	//myEntityManager->InitEntityManager();

	if (saveLoadManager != nullptr)
	{
		saveLoadManager->InitSaveLoadManager(this);
	}

	if (residentManager != nullptr)
	{
		residentManager->InitResidentManager(this);
	}
	if (buildingManager != nullptr)
	{
		buildingManager->InitBuildingManager(this);
	}
	if (uiManager != nullptr)
	{
		uiManager->InitUIManager(this);
	}
	/*if (unitManager)
	{
		unitManager->InitUnitManager(this);
	}*/
	if (resourceManager)
	{
		resourceManager->InitResourceManager(this);
	}

}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		// Cast it to your custom player controller class
		AcityBuilderPlayerController* myPC = Cast<AcityBuilderPlayerController>(PC);
		if (myPC)
		{

			myPC->GetCursorProjection(projectedMousePosition);

			if (GEngine)
			{
				// Print the FVector to the screen
				//GEngine->AddOnScreenDebugMessage(
				//	-1,        // Key (or -1 for no key and therefore no need to worry about overwriting previous messages)
				//	5.0f,      // Display duration in seconds
				//	FColor::Green, // Color of the text
				//	FString::Printf(TEXT("Projected Mouse Position: %s"), *projectedMousePosition.ToString()) // The text to display
				//);
			}
		}
	}
	if (timeManager != nullptr)
	{
		timeManager->UpdateTimeManager(DeltaTime);
	}
	if (residentManager != nullptr)
	{
		residentManager->UpdateResidentManager(DeltaTime);
	}
	if (buildingManager != nullptr)
	{
		buildingManager->UpdateBuildingManager();
	}
	if (uiManager != nullptr)
	{
		uiManager->UpdateUIManager(DeltaTime);
	}
	
}




void LoadGame()
{

}