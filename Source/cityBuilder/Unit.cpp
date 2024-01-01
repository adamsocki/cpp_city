// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"

AUnit::AUnit()
{
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	RootComponent = UnitMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Added/BasicUnit_testing_flip.BasicUnit_testing_flip'"));

	if (MeshAsset.Succeeded())
	{
		UnitMesh->SetStaticMesh(MeshAsset.Object);
		UStaticMesh* StaticMesh = UnitMesh->GetStaticMesh();

		FBoxSphereBounds Bounds = StaticMesh->GetBounds();
		boxExtents = Bounds.BoxExtent;

	}	


	occupied = false;
}




void AUnit::InitUnit(ABuilding* building)
{
	//FVector Offset = FVector(10.0f, 20.0f, 30.0f);

	buildingUnitIsIn = building;


}


void AUnit::SetCapacity(int32 cap)
{
	capacity = cap;
}



