// Fill out your copyright notice in the Description page of Project Settings.


#include "buildingManager.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
AbuildingManager::AbuildingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AbuildingManager::InitBuildingManager(AGameManager* gm)
{
	//Super::BeginPlay();

	gameManager = gm;
	//ABuilding *b;

	//buildings.Add(b);
	



	TArray<AActor*> FoundBuildingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding::StaticClass(), FoundBuildingActors);
	TArray<AActor*> FoundAgencyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAgency::StaticClass(), FoundAgencyActors);


	for (int i = 0; i < FoundBuildingActors.Num(); i++)
	{
		// ADD ALL BUILDINGS IN LEVEL TO AN ARRAY
		ABuilding* MyBuilding = Cast<ABuilding>(FoundBuildingActors[i]);
		if (MyBuilding != nullptr)
		{
			buildings.Add(MyBuilding);
			MyBuilding->InitBuilding(11, FVector(2,2,10));
			//buildings.Add(MyBuilding->entityHandle);
		}
	}

	for (int i = 0; i < FoundAgencyActors.Num(); i++)
	{
		AAgency* MyAgency = Cast<AAgency>(FoundAgencyActors[i]);
		if (MyAgency != nullptr)
		{
			agencies.Add(MyAgency);
			MyAgency->InitAgency();
			//buildings.Add(MyBuilding->entityHandle);
		}
	}


	TArray<AActor*> FoundPOEActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APortOfEntry::StaticClass(), FoundPOEActors);

	for (int i = 0; i < FoundPOEActors.Num(); i++)
	{
		
		// ADD PORTS OF ENTRY IN LEVEL TO AN ARRAY
		APortOfEntry* MyPortOfEntry = Cast<APortOfEntry>(FoundPOEActors[i]);
		if (MyPortOfEntry != nullptr)
		{
			portOfEntries.Add(MyPortOfEntry);
			MyPortOfEntry->InitPortOfEntry();
			//portOfEntries.Add(MyPortOfEntry->entityHandle);
		}
	}

	timeManager = Cast<ATimeManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass()));
}

// Called every frame
void AbuildingManager::UpdateBuildingManager()
{

	for (int i = 0; i < buildings.Num(); i++)
	{


		if (buildings[i])
		{
			buildings[i]->UpdateBuilding();
		}
	}

	for (int i = 0; i < portOfEntries.Num(); i++)
	{

		portOfEntries[i]->UpdatePortOfEntry();
		portOfEntries[i]->spawnTimer += GetWorld()->GetDeltaSeconds();
		//timeManager->IncrementTime(&portOfEntries[i]->spawnTimer);
	}

	for (int i = 0; i < agencies.Num(); i++)
	{
		agencies[i]->UpdateAgency();

	}
}

AUnit* AbuildingManager::GetBuildingUnitVacancy()
{
	AUnit* val = {};

	return val;
}

AActor* AbuildingManager::ReturnAgency()
{
	TArray<AActor*> FoundAgencyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAgency::StaticClass(), FoundAgencyActors);

	/*for (int i = 0; i < FoundAgencyActors.Num(); i++)
	{*/

	//}
	AActor* AgencyActor = FoundAgencyActors[0];

	return AgencyActor;
}

AActor* AbuildingManager::ReturnNearestAgency(FVector location)
{

	TArray<AActor*> FoundAgencyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAgency::StaticClass(), FoundAgencyActors);

	if (FoundAgencyActors.Num() == 0)
	{
		// No agencies found, return nullptr
		return nullptr;
	}

		
	AActor* ClosestAgencyActor = FoundAgencyActors[0];
	float MinDistance = FVector::Distance(location, ClosestAgencyActor->GetActorLocation());


	for (int i = 0; i < FoundAgencyActors.Num(); i++)
	{
		float DistanceToAgency = FVector::Distance(location, FoundAgencyActors[i]->GetActorLocation());
		if (DistanceToAgency < MinDistance)
		{
			MinDistance = DistanceToAgency;
			ClosestAgencyActor = FoundAgencyActors[i];
		}
	}

	return ClosestAgencyActor;
}


void AbuildingManager::PlaceBuilding(AActor* buildingToPlace)
{
	APortOfEntry* portOfEntry_place = Cast <APortOfEntry>(buildingToPlace);

	if (portOfEntry_place)
	{
		portOfEntries.Add(portOfEntry_place);
		return;
	}

	AAgency* agency_place = Cast <AAgency>(buildingToPlace);
	if (agency_place)
	{
		agencies.Add(agency_place);
		agency_place->InitAgency();
		return;
	}

	ABuilding* building_place = Cast <ABuilding>(buildingToPlace);
	if (building_place)
	{
		buildings.Add(building_place);
		return;
	}


}

