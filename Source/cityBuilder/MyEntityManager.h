// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "MyStructs.h"

#include "GameFramework/Actor.h"
#include "MyEntityManager.generated.h"


class AGameManager;


UCLASS()
class CITYBUILDER_API AMyEntityManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEntityManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void UpdateMyEntityManager();
	TArray<AMyEntity*> entities;

	FGameData* gameData;

	AMyEntity* GetEntity(FGameData* Data, FEntityHandle handle);
	FEntityHandle SpawnEntity(EEntityType type);


	int32 freeList[10000];
	int32 freeListCount;

	void InitEntityManager();
	void InitEntityBuffers();

	//AGameManager* gameManager;

};
