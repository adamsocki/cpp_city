// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_Class.h"

// Sets default values
AEntity_Class::AEntity_Class()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityMesh"));
	RootComponent = BuildingMesh;

}

void AEntity_Class::InitEntity()
{

}

void AEntity_Class::UpdateEntity()
{

}


