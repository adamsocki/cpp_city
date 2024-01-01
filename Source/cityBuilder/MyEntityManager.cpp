// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEntityManager.h"
#include "GameManager.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyEntityManager::AMyEntityManager()
{
	freeListCount = 0;

}

// Called when the game starts or when spawned
void AMyEntityManager::BeginPlay()
{
	Super::BeginPlay();
	//freeListCount = 0;
	
	TArray<AActor*> foundEntites;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyEntity::StaticClass(), foundEntites);
	
	for (AActor* a : foundEntites)
	{
		entities.Add(Cast<AMyEntity>(a));
	}

	AGameManager* gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));

	gameData = &gameManager->GameData;

	if (gameData)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GOT"));
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NotGot"));
	}

	InitEntityManager();
	InitEntityBuffers();
}

// Called every frame
void AMyEntityManager::UpdateMyEntityManager()
{
	//for (AMyEntity* entity : entities)
	//{
	//	
	//}
}

FEntityHandle AMyEntityManager::SpawnEntity(EEntityType type)
{
	int32 nextFreeIdInIndex = gameData->em.nextID;

	if (freeListCount > 0)
	{
		nextFreeIdInIndex = freeList[freeListCount - 1];
		freeListCount--;
	}
	else
	{
		gameData->em.nextID++;
	}

	FMyEntityInfo* info = &gameData->em.entities[nextFreeIdInIndex];
	info->type = type;
	info->generation= info->generation + 1;

	int32 bufferIndex = static_cast<int32>(type);
	FEntityTypeBuffer* buffer = &gameData->em.buffers[bufferIndex];
	info->indexInBuffer = buffer->count;
	buffer->count++;

	FEntityHandle handle = {};
	handle.generation = info->generation;
	handle.indexInInfo = nextFreeIdInIndex;
	handle.type = type;

	return handle;
}

void AMyEntityManager::InitEntityManager()
{
	gameData->em.entityCapacity = 6000;
	gameData->em.entities = (FMyEntityInfo*)malloc(sizeof(FMyEntityInfo) * gameData->em.entityCapacity);
	memset(gameData->em.entities, 0, sizeof(FMyEntityInfo) * gameData->em.entityCapacity);
	gameData->em.nextID = 0;
	
	int32 bufferIndexOfEntityTypes = static_cast<int32>(EEntityType::EntityType_Count);
	gameData->em.buffers = (FEntityTypeBuffer*)malloc(sizeof(FEntityTypeBuffer) * bufferIndexOfEntityTypes);
	memset(gameData->em.buffers, 0, sizeof(FEntityTypeBuffer) * bufferIndexOfEntityTypes);

	/*for (int i = 0; i < gameData->em.entityCapacity; i++)
	{
		gameData->em.entities[i].generation = 0;
	}*/


	//gameData->em.entityTypes[0] = EEntityType::EntityType_Resident;
	//gameData->em.entityTypes[0] = EntityType_Terrain;
	//gameData->em.entityTypes[2] = EntityType_Fern;
	//gameData->em.entityTypes[3] = EntityType_Wall;
}

void AMyEntityManager::InitEntityBuffers()
{


	int32 bufferIndexResident = static_cast<int32>(EEntityType::EntityType_Resident);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SpawnResident! %d"), bufferIndexResident));
	}
	FEntityTypeBuffer* residentBuffer = &gameData->em.buffers[bufferIndexResident];
	residentBuffer->capacity = 8000;
	residentBuffer->sizeInBytes = sizeof(AResident);
	residentBuffer->count = 0;
	//residentBuffer->entities = (AResident*)malloc(residentBuffer->capacity * residentBuffer->sizeInBytes);
	//memset(residentBuffer->entities, 0, sizeof(AResident) * residentBuffer->capacity);

	//residentBuffer->entitiesArray = (AResident*)malloc(residentBuffer->capacity * residentBuffer->sizeInBytes);
}


//AMyEntity* AMyEntityManager::GetEntity(FGameData* gd, FEntityHandle handle)
//{
//		if (handle.indexInInfo >= gd->em.entityCapacity) {
//			return NULL;
//		}
//
//		FMyEntityInfo* info = &gd->em.entities[handle.indexInInfo];
//
//		if (info->generation != handle.generation) {
//			return NULL;
//		}
//		if (info->typeNum != handle.typeNum) {
//			return NULL;
//		}
//
//		FEntityTypeBuffer* buffer = &gd->em.buffers[info->typeNum];
//
//
//
//		//TWeakObjectPtr<AMyEntity> var = buffer[info->indexInBuffer].entities;
//		//return var.Get();
//
//		//return ((uint8*)buffer->entities + (buffer->sizeInBytes * info->indexInBuffer));
//		//return AMyEntity;
//		//return NULL;
//
//}