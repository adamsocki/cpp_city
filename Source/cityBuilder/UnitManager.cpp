// Fill out your copyright notice in the Description page of Project Settings.



#include "GameManager.h"
#include "UnitManager.h"

// Sets default values
AUnitManager::AUnitManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AUnitManager::InitUnitManager(AGameManager* gm)
{



}

// Called every frame
void AUnitManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitManager::RegisterUnit(AUnit* unit)
{
	units.Add(unit);
}

