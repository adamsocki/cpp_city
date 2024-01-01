// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "MyEntity.h"


#include "Unit.generated.h"

/**
 * 
 */

class ABuilding;
class AResident;

UCLASS()
class CITYBUILDER_API AUnit : public AActor
{
	GENERATED_BODY()

public:
	AUnit();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* UnitMesh;
	
	void InitUnit(ABuilding* building);
	void SetCapacity(int32 cap);

	FVector boxExtents;

	bool occupied;
	int32 capacity;

	TArray<AResident*> residentsInUnit;


	ABuilding* buildingUnitIsIn;
	

};
