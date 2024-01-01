// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"

// Sets default values
AGround::AGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

    //bUseBooleanEnvironmentShadowing = true;
    

     // Create and configure the static mesh component.
    GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundMesh"));
    RootComponent = GroundMesh;

    // Set the mesh for the GroundMesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/PathToYourMesh/YourMesh.YourMesh'"));
    if (MeshAsset.Succeeded())
    {
        GroundMesh->SetStaticMesh(MeshAsset.Object);
    }

    // Set the mesh's collision properties.
    GroundMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GroundMesh->SetCollisionObjectType(ECC_WorldStatic);
    GroundMesh->SetCollisionResponseToAllChannels(ECR_Block);
}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();
	
}
