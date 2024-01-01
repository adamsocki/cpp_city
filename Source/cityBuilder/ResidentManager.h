// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Entity_Test.h"

#include "Resident.h"

#include "ResidentManager.generated.h"


class ABuildingManager;

UCLASS()
class CITYBUILDER_API AResidentManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResidentManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	void InitResidentManager(AGameManager* gm);
	void UpdateResidentManager(float deltaTime);
	void SpawnResident();

	TArray<AResident*> residents;
	TArray<AResident*> residentsToUpdate;

	TArray<FEntityHandle> residentHandles;

	void RegisterResident(AResident* resident);
	bool AssignResidentHome(AResident* resident);
	void AddToUpdateRoster(AResident* resident);
	void RemoveFromUpdateRoster(AResident *resident);

	AGameManager* gameManager;

	//ABuildingManager* buildingManager;


	//FEntity_Test entity_test;
};
