// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Unit.h"

#include "GameFramework/Actor.h"
#include "UnitManager.generated.h"




UCLASS()
class CITYBUILDER_API AUnitManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitManager();

	


public:	

	void InitUnitManager(AGameManager* gm);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RegisterUnit(AUnit* unit);



	TArray<AUnit*> units;
};
