// Fill out your copyright notice in the Description page of Project Settings.


#include "ResidentManager.h"
#include "GameManager.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AResidentManager::AResidentManager()
{
 	

}

// Called when the game starts or when spawned
void AResidentManager::BeginPlay()
{
	Super::BeginPlay();
	//entity_test.Handle = 10;



}
	

void AResidentManager::SpawnResident()
{

}


void AResidentManager::InitResidentManager(AGameManager* gm)
{

	gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	
}

void AResidentManager::RegisterResident(AResident* resident)
{
	residents.Add(resident);
	//residentHandles.Add(residentHandle);

	if (AssignResidentHome(resident))
	{

	}

}

bool AResidentManager::AssignResidentHome(AResident* resident)
{
	AbuildingManager* bm = gameManager->buildingManager;
	AUnit *unitFree = bm->GetBuildingUnitVacancy();
	
	if (unitFree)
	{
		resident->homeResidentialUnit = unitFree;
		return true;
	}
	else
	{
		return false;
	}

}

// Called every frame
void AResidentManager::UpdateResidentManager(float deltaTime)
{
	for (int i = 0; i < residents.Num(); i++)
	{
		//residents[i]->UpdateResident(deltaTime);
	}

	for (int i = 0; i < residentsToUpdate.Num(); i++)
	{
		residentsToUpdate[i]->UpdateResident(deltaTime);
	}
}

void AResidentManager::AddToUpdateRoster(AResident* resident)
{
	residentsToUpdate.Add(resident);
}

void AResidentManager::RemoveFromUpdateRoster(AResident *resident)
{
	if (resident)
	{
		residentsToUpdate.Remove(resident);

	}
}

