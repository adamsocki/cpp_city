// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveLoadManager.generated.h"


class AGameManager;

UCLASS()
class CITYBUILDER_API ASaveLoadManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveLoadManager();

public:	

	AGameManager* gameManager;
	
	void InitSaveLoadManager(AGameManager* gm);
	// Called every frame
	void UpdateSaveLoadManager();
};
