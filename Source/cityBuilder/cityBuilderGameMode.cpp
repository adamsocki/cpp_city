// Copyright Epic Games, Inc. All Rights Reserved.

#include "cityBuilderGameMode.h"
#include "cityBuilderPlayerController.h"
#include "cityBuilderCharacter.h"
#include "GameFramework/HUD.h"
#include "GameHUD.h"
#include "UObject/ConstructorHelpers.h"

AcityBuilderGameMode::AcityBuilderGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AcityBuilderPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerCameraBPClass(TEXT("/Game/TopDown/Blueprints/BP_CameraCharacter"));
	static ConstructorHelpers::FClassFinder<AHUD> MakingHUD(TEXT("/Game/TopDown/Blueprints/UI/BP_HUD"));

	
	if (PlayerCameraBPClass.Class != nullptr)
	{
		//DefaultPawnClass = PlayerPawnBPClass.Class;
		DefaultPawnClass = PlayerCameraBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}


	//HUDClass = AGameHUD::StaticClass();
	if (MakingHUD.Class != nullptr)
	{
		HUDClass = MakingHUD.Class;
	}





	/*	AHUD* test = Cast<AHUD>(HUDClass);
		
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/TopDown/Blueprints/BP_UIwidget"));
		if (WidgetClassFinder.Class != NULL)
		{
			GameHUDWidgetClass = WidgetClassFinder.Class;
			GameHUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameHUDWidgetClass);
			if (GameHUDWidget != nullptr)
			{
				GameHUDWidget->AddToViewport();
			}
		}*/


		
}