// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"


ABuilding::ABuilding()
{
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildMeshComponent"));
	DoorMesh->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Added/DoorBuilding_testing.DoorBuilding_testing'"));
	if (DoorMeshAsset.Succeeded())
	{
		DoorMesh->SetStaticMesh(DoorMeshAsset.Object);
	}
}

void ABuilding::InitBuilding(int32 unitCount, FVector unitDimention)
{
	SpawnUnit(unitCount);
	ConstructBuildingFromUnits(unitDimention);
	
	//CalculateFloorDimensions();
}

void ABuilding::AddUnitToBuilding(AUnit *unit)
{
	//units.Add(unit); 
}

void ABuilding::UpdateBuilding()
{

	//if (GEngine)
	//{
	//	//building
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Dim[0] X:%.2f"), floorDimensionsArray[0].X));
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Dim[0] Y:%.2f"), floorDimensionsArray[0].Y));
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Dim[0] Z:%.2f"), floorDimensionsArray[0].Z));

	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Box[0] X:%.2f"), units[0]->boxExtents.X));
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Box[0] Y:%.2f"), units[0]->boxExtents.Y));
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Box[0] Z:%.2f"), units[0]->boxExtents.Z));
	//}
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FString::Printf(TEXT("SpawnResident! %d"), bufferIndexResident));
		//											//FString::Printf(TEXT("SpawnResident! %d"), bufferIndexResident)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FString::Printf(TEXT("SpawnResident! %d"), bufferIndexResident));
}

void ABuilding::SpawnUnit(int32 count)
{
	for (int i = 0; i < count; i++)
	{
		FVector locationToSpawn(this->GetActorLocation());
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		AUnit* spawnedUnit = GetWorld()->SpawnActor<AUnit>(locationToSpawn, Rotation, SpawnInfo);
		//USceneComponent* ParentComponent;

		spawnedUnit->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		spawnedUnit->buildingUnitIsIn = this;
		spawnedUnit->capacity = 1;

		units.Add(spawnedUnit);
	}
}


void ABuilding::ConstructBuildingFromUnits(FVector unitSize)
{

	buildingDimentions = FVector(0.0f, 0.0f, 0.0f);
	// = FVector(0.0f, 0.0f, 0.0f);

	/*int32 currentWidth = 1;
	int32 currentDepth = 1;
	int32 currentHeight = 1;*/

	int32 unitCounter = 0;

	totalBuildingUnits = unitSize.X * unitSize.Y * unitSize.Z;


	for (int z = 0; z < unitSize.Z; z++)
	{
		for (int y = 0; y < unitSize.Y; y++)
		{
			for (int x = 0; x < unitSize.X; x++)
			{
				if (unitCounter < units.Num())
				{
					units[unitCounter]->SetActorRelativeLocation(FVector(x * units[unitCounter]->boxExtents.X * 2, y * units[unitCounter]->boxExtents.Y * 2, z * units[unitCounter]->boxExtents.Z * 2));
					//buildingDimentions.X += units[unitCounter]->boxExtents.X;
				}
				unitCounter++;
			}
			
		}
	}

	
	int32 unitFloorCounter = 0;
	
	for (int z = 0; z < unitSize.Z; z++)
	{
		floorDimensionsArray.Add(CalculateFloorDimensions());
	}
	
	
	PlaceDoor();

	//for (int z = 0; z < buildingHeight; z++) {
	//	FVector floorDimensions(0.0f, 0.0f, 0.0f);
	//	for (int y = 0; y < buildingDepth; y++) {
	//		for (int x = 0; x < buildingWidth; x++) {
	//			if (unitFloorCounter < units.Num()) {
	//				// Assuming boxExtents is half the width/depth/height of the unit
	//				FVector unitLocation(x * units[unitFloorCounter]->boxExtents.X * 2, y * units[unitFloorCounter]->boxExtents.Y * 2, z * units[unitFloorCounter]->boxExtents.Z * 2);
	//				//units[unitCounter]->SetActorRelativeLocation(unitLocation);
	//				// Update floor dimensions based on this unit's position and size
	//				floorDimensions.X = FMath::Max(floorDimensions.X, unitLocation.X + units[unitFloorCounter]->boxExtents.X);
	//				floorDimensions.Y = FMath::Max(floorDimensions.Y, unitLocation.Y + units[unitFloorCounter]->boxExtents.Y);
	//				// Assuming all units on the same floor have the same Z size
	//				floorDimensions.Z = units[unitFloorCounter]->boxExtents.Z * 2;
	//			}
	//			unitFloorCounter++;
	//		}
	//	}
	//	// Add this floor's dimensions to the array
	//	floorDimensionsArray.Add(floorDimensions);
	//}
	//FVector floorDimensions(0.0f, 0.0f, 0.0f);
	////floorDimensionsArray = CalculateBuildingDimensionsPerFloor();
	//// Track the furthest extent in each direction
	//FVector currentExtent(0.0f, 0.0f, 0.0f);
	//for (int y = 0; y < buildingDepth; ++y) {
	//	for (int x = 0; x < buildingWidth; ++x) {
	//		int32 unitIndex = y * buildingWidth + x;
	//		if (unitIndex < units.Num()) {
	//			//const FUnit& unit = units[unitIndex];
	//			currentExtent.X = (x + 1) * units[unitIndex]->boxExtents.X * 2;
	//			currentExtent.Y = FMath::Max(currentExtent.Y, (y + 1) * units[unitIndex]->boxExtents.Y * 2);
	//			floorDimensions.Z = FMath::Max(floorDimensions.Z, units[unitIndex]->boxExtents.Z * 2);
	//		}
	//	}
	//	floorDimensions.X = FMath::Max(floorDimensions.X, currentExtent.X);
	//	floorDimensions.Y = FMath::Max(floorDimensions.Y, currentExtent.Y);
	//}
	//floorDimensionsArray.Add(floorDimensions);


}


FVector ABuilding::CalculateFloorDimensions() {
	FVector floorDimensions(0.0f, 0.0f, 0.0f);

	// Track the furthest extent in each direction.
	FVector currentExtent(0.0f, 0.0f, 0.0f);

	for (int y = 0; y < buildingDepth; ++y) {
		for (int x = 0; x < buildingWidth; ++x) {
			int32 unitIndex = y * buildingWidth + x;
			if (unitIndex < units.Num()) {
				currentExtent.X = (x + 1) * units[unitIndex]->boxExtents.X * 2;
				currentExtent.Y = FMath::Max(currentExtent.Y, (y + 1) * units[unitIndex]->boxExtents.Y * 2);
				floorDimensions.Z = FMath::Max(floorDimensions.Z, units[unitIndex]->boxExtents.Z * 2);
			}
		}
		floorDimensions.X = FMath::Max(floorDimensions.X, currentExtent.X);
		floorDimensions.Y = FMath::Max(floorDimensions.Y, currentExtent.Y);
	}

	return floorDimensions;
}


// THIS IS NOT COMPLETE AND WONT WORK YET
//TArray<FVector> ABuilding::CalculateBuildingDimensionsPerFloor() {
//	TArray<FVector> floorDimensionsArray;
//
//	for (const TArray<AUnit>& floorUnits : floors) 
//	{
//	// Assume buildingWidth and buildingDepth are known per floor.
//		int32 buildingWidth = ...; // Define these based on your logic.
//		int32 buildingDepth = ...; // Define these based on your logic.
//		FVector floorDimensions = CalculateFloorDimensions(floorUnits, buildingWidth, buildingDepth);
//		floorDimensionsArray.Add(floorDimensions);
//	}
//
//	return floorDimensionsArray;
//}


void ABuilding::PlaceDoor()
{
	float buildingWidthSize = floorDimensionsArray[0].X;
	FVector setDoorLocation = FVector(buildingWidthSize, floorDimensionsArray[0].Y / 2, 0.0f);
	DoorMesh->SetRelativeLocation(setDoorLocation);
	hasEntranceLocation = true;
	entranceLocation = setDoorLocation;
	entranceLocation.X /= 2.0f;

}

