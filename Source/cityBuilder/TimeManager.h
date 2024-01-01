// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



#include "TimeManager.generated.h"



UCLASS()
class CITYBUILDER_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();


	void UpdateTimeManager(float DeltaTime);
	void IncrementTime(float* time);
	 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/*MyTimer* spawnTimer;
	MyTimer* gameTimer;*/

	TArray<float> timers;

	float deltaTime;
	float gameTimer;
	double  LastFunctionCallTime;
};
