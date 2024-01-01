// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "ResourceManager.generated.h"


class AGameManager;

UCLASS()
class CITYBUILDER_API AResourceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();


	void InitResourceManager(AGameManager* gm);
	void UpdateResourceManager(float deltaTime);


	float cash;


};
