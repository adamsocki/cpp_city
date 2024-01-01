// Fill out your copyright notice in the Description page of Project Settings.


#include "Resident.h"
#include "Agency.h"
#include "buildingManager.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AAgency::AAgency()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	AgencyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
	RootComponent = AgencyMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Added/AgencyBuilding_testing.AgencyBuilding_testing'"));
	if (MeshAsset.Succeeded())
	{
		AgencyMesh->SetStaticMesh(MeshAsset.Object);
	}


	isOpen = true;
	queueCount = 1;
	assignmentTime = 1.0f;
	maxAllowedInQueue = 10;
	inPlacementMode = 0;
	//residentsInQueue = {};
}



void AAgency::InitAgency()
{
	buildingManager = Cast<AbuildingManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AbuildingManager::StaticClass()));
	timeManager = Cast<ATimeManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass()));
	//SetActorEnableCollision(false);
}

void AAgency::UpdateAgency()
{
	TArray<AResident*> residentsToRemoveFromQueue = {};

	for (int i = 0; i < residentsInQueue.Num(); i++)
	{
		if (i < queueCount)
		{
			residentsInQueue[i]->inQueueTimer += GetWorld()->DeltaTimeSeconds;
		}

		if (residentsInQueue[i]->inQueueTimer > assignmentTime)
		{
			//residentsInQueue[i]
			// ASSIGN RESIDENT TO WHERE THEY ARE TYRING TO GO THEN LET THEM UPDATE AGAIN IN RESIDENT MANAGER
			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("TimerEndQueue %f"), residentsInQueue[i]->inQueueTimer));*/
			

			switch (residentsInQueue[i]->assignmentState)
			{
				case EAssingmentType::AssingmentType_ToHome:
				{
					if (AttemptHomeAssignment(residentsInQueue[i]))
					{

						
						residentsToRemoveFromQueue.Add(residentsInQueue[i]);
						residentsInQueue[i]->TriggerBox->SetGenerateOverlapEvents(true);
						//residentsInQueue[i]->SetActorEnableCollision(true);
					}
					else
					{
						residentsInQueue[i]->AssignRandomWander();
						residentsInQueue[i]->assignmentState = EAssingmentType::AssingmentType_Count;
						residentsToRemoveFromQueue.Add(residentsInQueue[i]);
						residentsInQueue[i]->AddToUpdateRoster();
						residentsInQueue[i]->inQueueTimer = 0.0f;
						
					}
				}
				default:
				{

				}
			}
			
		}


	}

	for (int i = 0; i < residentsToRemoveFromQueue.Num(); i++)
	{
		residentsInQueue.Remove(residentsToRemoveFromQueue[i]);
	}

}



bool AAgency::AcceptResident(AResident* resident)
{
	bool willAcceptResident = false;

	if (isOpen)
	{
		willAcceptResident = true;
	}

	if (residentsInQueue.Num() >= maxAllowedInQueue)
	{
		willAcceptResident = false;
	}
	

	//// RUN OTHER CHECKS ON RESIDENT ELEGEBILITY TO BE IN AGENCY
	//


	return willAcceptResident;
}

void AAgency::AddResidentToQueue(AResident* resident)
{
	residentsInQueue.Add(resident);
	resident->assignmentState = EAssingmentType::AssingmentType_ToHome;
}


void AAgency::AssignResident(EAssingmentType assignmentType, AResident* resident)
{
	
	/*switch (assignmentType)
	{
		case EAssingmentType::AssingmentType_ToHome:
		{

		}
		default:
		{

		}
	}*/
}

bool AAgency::AttemptHomeAssignment(AResident* resident)
{

	for (int i = 0; i < buildingManager->buildings.Num(); i++)
	{
		for (int j = 0; j < buildingManager->buildings[i]->units.Num(); j++)
		{
			AUnit* possibleUnit = buildingManager->buildings[i]->units[j];
			if (possibleUnit->capacity > possibleUnit->residentsInUnit.Num())
			{
			//	/*if (GEngine)
			//	{
			//		FString actorToMoveToString = "actorToMoveTo->GetName()";
			//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, actorToMoveToString);
			//	}*/

				possibleUnit->residentsInUnit.Add(resident);
			//	//resident->InitResidentAssignment();
			//	
				resident->assignmentState = EAssingmentType::AssingmentType_Count;
				resident->residentState = EResidentState::ResidentState_Moving;
				resident->actorToMoveTo = buildingManager->buildings[i];
				resident->AddToUpdateRoster();
				resident->hasHome = true;
				resident->TriggerBox->SetGenerateOverlapEvents(true);

				return true;
			}
			else
			{
				//resident->actorToMoveTo = buildingManager->buildings[i];
			}
		}
	}

	return false;
}

void AAgency::RandomMoveLocation()
{



}






