// Fill out your copyright notice in the Description page of Project Settings.


#include "ResidentActor_TESTINSTAT.h"

// Sets default values
AResidentActor_TESTINSTAT::AResidentActor_TESTINSTAT()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
    ResidentMeshInstances = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("ResidentMeshInstances"));
    RootComponent = ResidentMeshInstances;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
    if (MeshAsset.Succeeded())
    {
        ResidentMeshInstances->SetStaticMesh(MeshAsset.Object);
    }
}

int32 AResidentActor_TESTINSTAT::AddResidentInstance(const FVector& Location)
{
    FTransform InstanceTransform;
    InstanceTransform.SetLocation(Location);
    return ResidentMeshInstances->AddInstance(InstanceTransform);
}



void AResidentActor_TESTINSTAT::UpdateResidentInstanceTransform(int32 InstanceIndex, const FTransform& NewTransform)
{
    if (ResidentMeshInstances && ResidentMeshInstances->GetInstanceCount() > InstanceIndex)
    {
        ResidentMeshInstances->UpdateInstanceTransform(InstanceIndex, NewTransform, true, true);
    }
}