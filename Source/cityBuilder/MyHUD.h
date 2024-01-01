// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API AMyHUD : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="HUD COMMANDS")
	void ClickTester();
	
};
