// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResidentLifecycle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYBUILDER_API UResidentLifecycle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResidentLifecycle();

	//void AssignToAgency();

	//void AssignRandomWander();
		
};
