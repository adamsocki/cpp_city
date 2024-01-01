// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "GameManager.h"
#include "PortOfEntry.h"
#include "Blueprint/WidgetTree.h"

// Sets default values
AUIManager::AUIManager()
{
//	  static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/MyWidgetBlueprint"));
	//if (WidgetClassFinder.Succeeded())
	//{
	//	GameWidgetClass = WidgetClassFinder.Class;
	//}


	
	hoverButton = false;
}




void AUIManager::InitUIManager(AGameManager* gm)
{

	if (GameWidget)
	{
		GameWidget->AddToViewport(0);
	}
	
	gameManager = gm;
	buildingManager = gm->buildingManager;
	//FText va =  FText("HI");
	

	//if (GameWidgetClass != nullptr)
	//{
		// Create the widget and add it to the viewport
		/*GameWidget = Cast<UUserWidget>(CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass));
		if (GameWidget)
		{
			GameWidget->AddToViewport();
		}*/
//	}

	if (GameWidget)
	{
		UWidgetTree* a = GameWidget->WidgetTree;

		if (a)
		{

			TArray<UWidget*> widgets;
			UWidget* parent = a->RootWidget;
			a->GetChildWidgets(parent, widgets);

			FName cashName = "Cash_Resource";
			//FName CashClassName = a->FindWidget(cashName)->GetClass()->GetFName();

			FName buttonPOEname = "PortOfEntryButton";
			FName buttonBuildingname = "BuildingButton";
			FName agencyName = "AgencyButton";
			FName debugText = "DebugMode";
			FName actorDebugName = "actor_debug_001";

			cash = Cast<UTextBlock>(a->FindWidget(cashName));

			poeButton = Cast<UButton>(a->FindWidget(buttonPOEname));
			poeButton->OnClicked.AddDynamic(this, &AUIManager::SpawnPOEBuilding);
			poeButton->OnHovered.AddDynamic(this, &AUIManager::OnButtonHover);
			poeButton->OnUnhovered.AddDynamic(this, &AUIManager::OnButtonUnHover);

			buildingButton = Cast<UButton>(a->FindWidget(buttonBuildingname));
			buildingButton->OnClicked.AddDynamic(this, &AUIManager::SpawnBuildingBuilding);
			buildingButton->OnHovered.AddDynamic(this, &AUIManager::OnButtonHover);
			buildingButton->OnUnhovered.AddDynamic(this, &AUIManager::OnButtonUnHover);

			agencyButton = Cast<UButton>(a->FindWidget(agencyName));
			agencyButton->OnClicked.AddDynamic(this, &AUIManager::SpawnAgencyBuilding);
			agencyButton->OnHovered.AddDynamic(this, &AUIManager::OnButtonHover);
			agencyButton->OnUnhovered.AddDynamic(this, &AUIManager::OnButtonUnHover);

			debugIndicatorText = Cast<UTextBlock>(a->FindWidget(debugText));
			actorDebugText = Cast<UTextBlock>(a->FindWidget(actorDebugName));
			
			////////////////////
			////////////////////
			//	DISPLAY CERTIN UI ELEMENTS ONLY IN DEBUG MODE
			////////////////////
			////////////////////
			if (!gameManager->debugMode)
			{
				debugIndicatorText->SetVisibility(ESlateVisibility::Hidden);
				actorDebugText->SetVisibility(ESlateVisibility::Hidden);
			}

		}
	}

}


void AUIManager::OnPlacementTriggered()
{

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PlacementTrigger: %f"), 1.0f));
}

void AUIManager::UpdateUIManager(float deltaTime)
{
	
	if (cash)
	{

		FString val = "Cash: $";
		val.Append(FString::SanitizeFloat(gameManager->resourceManager->cash));
		cash->SetText(FText::FromString(val));
		
	}

	if (poeButton)
	{
		//(LogTemp, Warning, TEXT("Butotn"));

	}

	if (gameManager->controllerState == EControllerState::ControllerState_Placement)
	{
		UpdatePlacement();
		
	}
	if (actorDebugText)
	{
		FString residentDebugTextString = "Residents Active: ";
		residentDebugTextString.Append(FString::FromInt(gameManager->residentManager->residentsToUpdate.Num()));
		residentDebugTextString.Append("/ Total: ");
		residentDebugTextString.Append(FString::FromInt(gameManager->residentManager->residents.Num()));
		actorDebugText->SetText(FText::FromString(residentDebugTextString));
	}

	
}


void AUIManager::UpdatePlacement()
{
	if (temporaryPOEpawn && temporaryPOEpawn->inPlacementMode)
	{
		temporaryPOEpawn->SetActorLocation(gameManager->projectedMousePosition);
	}
	else if (temporaryBuildingPawn && temporaryBuildingPawn->inPlacementMode)
	{
		temporaryBuildingPawn->SetActorLocation(gameManager->projectedMousePosition);
	}
	else if (temporaryAgencyPawn && temporaryAgencyPawn->inPlacementMode)
	{
		temporaryAgencyPawn->SetActorLocation(gameManager->projectedMousePosition);
	}
}

void AUIManager::TestInput()
{

	if (!hoverButton && gameManager->controllerState == EControllerState::ControllerState_Placement)
	{
		
		if (temporaryPOEpawn && temporaryPOEpawn->inPlacementMode)
		{
			buildingManager->PlaceBuilding(temporaryPOEpawn);
			temporaryPOEpawn = {};
		}
		else if (temporaryBuildingPawn && temporaryBuildingPawn->inPlacementMode)
		{
			buildingManager->PlaceBuilding(temporaryBuildingPawn);
			temporaryAgencyPawn = {};
		}
		else if (temporaryAgencyPawn && temporaryAgencyPawn->inPlacementMode)
		{
			buildingManager->PlaceBuilding(temporaryAgencyPawn);
			temporaryAgencyPawn = {};

		}

		
		gameManager->controllerState = EControllerState::ControllerState_None;


	}
}



void AUIManager::SpawnPOEBuilding()
{
	ClearPlacers();

	gameManager->controllerState = EControllerState::ControllerState_Placement;

	locationToSpawn = FVector(gameManager->projectedMousePosition);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Owner = this;
	temporaryPOEpawn = GetWorld()->SpawnActor<APortOfEntry>(FVector(gameManager->projectedMousePosition), Rotation, SpawnInfo);
	temporaryPOEpawn->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	temporaryPOEpawn->inPlacementMode = true;

}

void AUIManager::SpawnBuildingBuilding()
{
	ClearPlacers();

	gameManager->controllerState = EControllerState::ControllerState_Placement;

	locationToSpawn = FVector(gameManager->projectedMousePosition);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Owner = this;

	temporaryBuildingPawn = GetWorld()->SpawnActor<ABuilding>(FVector(gameManager->projectedMousePosition), Rotation, SpawnInfo);
	temporaryBuildingPawn->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	temporaryBuildingPawn->inPlacementMode = true;
	FVector buildingUnitDimentions = FVector(3, 3, 4);
	int32 buildingUnitCount = 25;
	temporaryBuildingPawn->InitBuilding(buildingUnitCount, buildingUnitDimentions);

}

void AUIManager::SpawnAgencyBuilding()
{
	ClearPlacers();

	gameManager->controllerState = EControllerState::ControllerState_Placement;

	locationToSpawn = FVector(gameManager->projectedMousePosition);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Owner = this;

	temporaryAgencyPawn = GetWorld()->SpawnActor<AAgency>(FVector(gameManager->projectedMousePosition), Rotation, SpawnInfo);
	temporaryAgencyPawn->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	temporaryAgencyPawn->inPlacementMode = true;
	
}

void AUIManager::OnButtonHover()
{
	hoverButton = true;
}
void AUIManager::OnButtonUnHover()
{
	hoverButton = false;
}

void AUIManager::ClearPlacers()
{

	if (gameManager->controllerState == EControllerState::ControllerState_Placement)
	{

		if (temporaryPOEpawn)
		{
			temporaryPOEpawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			//GetWorld()->RemoveActor(temporaryPOEpawn,true);
			temporaryPOEpawn->Destroy();
			temporaryPOEpawn = nullptr;

		}
		else if (temporaryBuildingPawn)
		{
			//GetWorld()->RemoveActor(temporaryBuildingPawn, true);

			temporaryBuildingPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			
			TArray<AActor*> AttachedActors;
			temporaryBuildingPawn->GetAttachedActors(AttachedActors);
			for (AActor* ChildActor : AttachedActors)
			{
				// Recursively call this function in case the children have their own children
				ChildActor->Destroy();
			}

			temporaryBuildingPawn->Destroy();
			temporaryBuildingPawn = nullptr;
		}
		else if (temporaryAgencyPawn)
		{
			//GetWorld()->RemoveActor(temporaryAgencyPawn, true);
			temporaryAgencyPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			temporaryAgencyPawn->Destroy();
			temporaryAgencyPawn = nullptr;

		}

		gameManager->controllerState = EControllerState::ControllerState_None;


	}
}