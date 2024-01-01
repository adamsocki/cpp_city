// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Unit.h"

#include "Building.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API ABuilding : public AActor
{
	GENERATED_BODY()


public:

	ABuilding();

	FEntityHandle handle;

	virtual void UpdateBuilding();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* DoorMesh;


	void InitBuilding(int32 count, FVector size);
	void AddUnitToBuilding(AUnit *unit);

	//TArray<AResident*> residents;
	
	void SpawnUnit(int32 unitCount);
	

	int32 buildingWidth;
	int32 buildingDepth;
	int32 buildingHeight;
	int32 totalBuildingUnits;

	FVector buildingDimentions;
	bool hasEntranceLocation;
	FVector entranceLocation;

	TArray<AUnit*> units;
	TArray<TArray<AUnit*>> floorUnits;


	TArray<FVector> floorDimensionsArray;

	void ConstructBuildingFromUnits(FVector unitSize);
	FVector CalculateFloorDimensions();
	TArray<FVector> CalculateBuildingDimensionsPerFloor();
	void PlaceDoor();

	// called in init placement
	FVector buildingUnitDimentions;
	int32 buildingUnitCount;
	bool inPlacementMode;
};
