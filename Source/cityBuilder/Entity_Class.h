// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity_Class.generated.h"

UCLASS()
class CITYBUILDER_API AEntity_Class : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntity_Class();

protected:



public:	

	void InitEntity();
	
	virtual void UpdateEntity();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* BuildingMesh;

};
