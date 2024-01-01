// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "PortOfEntry.h"
#include "MyStructs.h"
#include <Components/BoxComponent.h>
#include "ResidentLifecycle.h"

#include "Resident.generated.h"

/**
 * 
 */

class AResidentManager;
class AbuildingManager;

UCLASS()
class CITYBUILDER_API AResident : public AMyEntity
{
	GENERATED_BODY()
private: 

	AResidentManager* residentManager;
	AbuildingManager* buildingManager;

public:

	AResident();
	FEntityHandle spawnPort;
	EResidentState residentState;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	EAssingmentType assignmentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* ResidentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UResidentLifecycle* residentLifecycle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	float movementSpeed;



	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void InitResident(APortOfEntry* portEntity);
	void UpdateResident(float deltaTime);
	void MoveSpecial(float deltaTime);
	void MoveResidentToPlace(AActor* actor, float deltaTime);
	void MoveResidentToLocation(FVector location, float deltaTime);

	void PrintWorking();
	void AddToUpdateRoster();
	void RemoveFromUpdateRoster();
	void RandomMoveLocation();
	void AssignRandomWander();
	//void InitResidentAssignment(AActor* placetoMoveTo);

	bool toUpdate;
	float inQueueTimer;
	bool hasHome;
	bool isWandering;
	int32 wanderCount;
	FVector destinationLocation;
	
	
	AActor* ActorControllingResident;
	AActor* actorToMoveTo;

	AUnit* homeResidentialUnit;

};
