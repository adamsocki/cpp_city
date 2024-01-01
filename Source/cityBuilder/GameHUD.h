// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Blueprint/UserWidget.h"

#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	AGameHUD();


	// Widget reference exposed to Blueprints
	/*UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUserWidget* MyWidgetInstance;*/
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY()
	UUserWidget* GameWidget;
};
