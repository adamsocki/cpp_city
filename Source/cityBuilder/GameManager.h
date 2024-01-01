// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveLoadManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "buildingManager.h"
#include "ResidentManager.h"
#include "MyEntityManager.h"
#include "UIManager.h"
#include "UnitManager.h"

#include "MyStructs.h"

#include "GameManager.generated.h"


UCLASS(Blueprintable)
class CITYBUILDER_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	EGameMode gameMode; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	bool debugMode;


	FGameData GameData;
	EControllerState controllerState;

	APlayerController* PC;
	FVector projectedMousePosition;



	ASaveLoadManager* saveLoadManager;
	ATimeManager* timeManager;
	AResourceManager* resourceManager;
	AbuildingManager* buildingManager;
	AResidentManager* residentManager;

	
	AUIManager* uiManager;
	AMyEntityManager* myEntityManager;
	AUnitManager* unitManager;

};
