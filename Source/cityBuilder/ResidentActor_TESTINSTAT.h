// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/HierarchicalInstancedStaticMeshComponent.h>


#include "ResidentActor_TESTINSTAT.generated.h"

UCLASS()
class CITYBUILDER_API AResidentActor_TESTINSTAT : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResidentActor_TESTINSTAT();


public:	
	// Called every frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* ResidentMeshInstances;

	int32  AddResidentInstance(const FVector& Location);
	void UpdateResidentInstanceTransform(int32 InstanceIndex, const FTransform& NewTransform);
};