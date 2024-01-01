// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Building.h"
#include "Agency.h"
#include "PortOfEntry.h"
#include "TimeManager.h"

#include "buildingManager.generated.h"

UCLASS()
class CITYBUILDER_API AbuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AbuildingManager();

protected:
	// Called when the game starts or when spawned

public:	

	void InitBuildingManager(AGameManager* gm);

	// Called every frame
	void UpdateBuildingManager();

	AUnit* GetBuildingUnitVacancy();
	AActor* ReturnAgency();
	AActor* ReturnNearestAgency(FVector location);
	bool AreThereOtherAgencies(AAgency* agency);

	// TArray of ACustomActor objects
	//UPROPERTY(BlueprintReadOnly, Category = "Buildings")
	TArray<ABuilding*> buildings;
	//TArray<FEntityHandle> buildings;
	TArray<APortOfEntry*> portOfEntries;
	//TArray<FEntityAAHandle> portOfEntries;

	TArray<AAgency*> agencies;


	void PlaceBuilding(AActor* buildingToPlace);


	ATimeManager* timeManager;
	AGameManager* gameManager;


};
