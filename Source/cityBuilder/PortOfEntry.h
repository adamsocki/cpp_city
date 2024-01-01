// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "TimeManager.h"


#include "PortOfEntry.generated.h"

/**
 * 
 */
class AResident;

UCLASS()
class CITYBUILDER_API APortOfEntry : public AActor
{
	GENERATED_BODY()

public:
	float spawnTimer = 0.0f;
	bool inPlacementMode;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* BuildingMesh;

	APortOfEntry();

	void InitPortOfEntry();
	//virtual void UpdateBuilding() override;
	void UpdatePortOfEntry();


	void SpawnResident();

	FEntityHandle residentHandle;

	void PrintResidentHandle();

	bool hasResidentReference;

	UPROPERTY()
	//TArray<AResident*> buildings;
	TArray<AResident*> residents;

};
