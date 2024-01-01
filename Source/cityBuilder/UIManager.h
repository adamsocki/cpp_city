// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "InputAction.h"

#include "UIManager.generated.h"


class AGameManager;
class AbuildingManager;
class APortOfEntry;
class ABuilding;
class AAgency;


UCLASS()
class CITYBUILDER_API AUIManager : public AActor
{
	GENERATED_BODY()



	
public:	
	// Sets default values for this actor's properties
	AUIManager();

	void OnPlacementTriggered();

	void InitUIManager(AGameManager* gm);
	void UpdateUIManager(float deltaTime);
	void UpdatePlacement();

	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestInput();

	AGameManager* gameManager;
	AbuildingManager *buildingManager;
	bool hoverButton;
	bool ctrlHeld;


	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* GameWidget;


	UTextBlock* cash;
	UPROPERTY(meta = (BindWidget))
	UButton* poeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* buildingButton;
	UPROPERTY(meta = (BindWidget))
	UButton* agencyButton;

	UButton* DoneButton;
	UTextBlock* debugIndicatorText;
	UTextBlock* actorDebugText;

	//UFUNCTION() 
	//void TestInput();
	UFUNCTION(BlueprintCallable, Category = "Test")
	void SpawnPOEBuilding();
	UFUNCTION(BlueprintCallable, Category = "Test")
	void SpawnBuildingBuilding();
	UFUNCTION(BlueprintCallable, Category = "Test")
	void SpawnAgencyBuilding();

	void OnButtonHover();
	void OnButtonUnHover();

	void ClearPlacers();

	
	APortOfEntry *temporaryPOEpawn;
	ABuilding* temporaryBuildingPawn;
	AAgency* temporaryAgencyPawn;
	FVector locationToSpawn;




};
