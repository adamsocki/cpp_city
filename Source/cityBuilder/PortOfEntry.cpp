// Fill out your copyright notice in the Description page of Project Settings.


#include "PortOfEntry.h"
#include "Resident.h"
#include "GameManager.h"

#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>



APortOfEntry::APortOfEntry()
{
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'"));
	if (MeshAsset.Succeeded())
	{
		BuildingMesh->SetStaticMesh(MeshAsset.Object);
	}
	inPlacementMode = false;


}

void APortOfEntry::InitPortOfEntry()
{
	//residentHandle = FEntityHandle();
	//hasResidentReference = false;

	SetActorEnableCollision(false);
}

void APortOfEntry::UpdatePortOfEntry()
{
	//Super::UpdateBuilding();



	if (spawnTimer > 3.0f)
	{
		SpawnResident();
	}







	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SpawnResident timer: %f"), spawnTimer));*/


		//	gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
//	AMyEntityManager* em = gameManager->myEntityManager;
	/*AResident* resident = (AResident*)em->GetEntity(&gameManager->GameData, residentHandle);
	resident->MoveSpecial(GetWorld()->GetDeltaSeconds());
	resident->PrintWorking();*/



	/*for (int i = 0; i < residents.Num(); i++)
	{
		residents[i]->MoveSpecial(GetWorld()->GetDeltaSeconds());
	}*/

	



	//void* GenericPtr = (em->GetEntity(&gameManager->GameData, residentHandle));
	//AResident* ResidentPtr = static_cast<AResident*>(GenericPtr);
	
	//if (residentHandle.isInit)
	//{
	////	void* GenericPtr = (em->GetEntity(&gameManager->GameData, residentHandle));
	////	AResident* ResidentPtr = static_cast<AResident*>(GenericPtr);

	////	ResidentPtr->PrintWorking();
	//}
	//

	//if (hasResidentReference)
	//{
	//	//AResident* resident = Cast<AResident>(em->GetEntity(&gameManager->GameData, residentHandle));
	////	if (resident)
	//	//{
	//		//resident->MoveSpecial(GetWorld()->GetDeltaSeconds());

	//	//}
	//	//resident->PrintWorking();
	//}
	

	PrintResidentHandle();
}

void APortOfEntry::SpawnResident()
{

	FVector locationToSpawn(this->GetActorLocation());
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AResident* spawnedResident = GetWorld()->SpawnActor<AResident>(locationToSpawn,Rotation, SpawnInfo);

	spawnedResident->InitResident(this);	
	
	spawnTimer = 0.0f;
}

void APortOfEntry::PrintResidentHandle()
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SpawnResident timer: %d"), residentHandle.indexInInfo));*/
}
