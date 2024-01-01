// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStructs.h"

#include "Agency.generated.h"



class AbuildingManager;
class ATimeManager;
class AResident;

UCLASS()
class CITYBUILDER_API AAgency : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgency();

protected:
	// Called when the game starts or when spawned
	

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AgentMesh")
	UStaticMeshComponent* AgencyMesh;


	bool inPlacementMode;

	bool isOpen;
	int32 maxAllowedInQueue;
	UPROPERTY(EditAnywhere, Category = "Queue Count Type")
	int32 queueCount;
	float assignmentTime;
	TArray<AResident*> residentsInQueue;


	void InitAgency();
	void UpdateAgency();
	bool AcceptResident(AResident* resident);
	void AddResidentToQueue(AResident* resident);
	void AssignResident(EAssingmentType assignmentType, AResident* resident);
	bool AttemptHomeAssignment(AResident* resident);
	void RandomMoveLocation();
	

	AbuildingManager* buildingManager;
	ATimeManager* timeManager;

	UPROPERTY(EditAnywhere, Category = "Agnecy Type")
	EAgencyType agencyType;



	


};

