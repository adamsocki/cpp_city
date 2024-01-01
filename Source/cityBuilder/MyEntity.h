// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStructs.h"
//#include "MyEntityManager.h"

#include "MyEntity.generated.h"

class AGameManager;

UCLASS()
class CITYBUILDER_API AMyEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEntity();

public:	
	void InitEntity(EEntityType type, AGameManager* gm);
	virtual void UpdateEntity(float deltaTime);

	//FEntityHandle handle;

	AGameManager* gameManager;
	//FEntityHandle entityHandle;

	
};
