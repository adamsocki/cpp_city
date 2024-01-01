// Copyright Epic Games, Inc. All Rights Reserved.

#include "cityBuilderPlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
//#include "ConstructorHelpers.h"
#define LANDSCAPE ECC_GameTraceChannel1

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "cityBuilderCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Logging/StructuredLog.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "UIManager.h"
#include "GameManager.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AcityBuilderPlayerController::AcityBuilderPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	allowCameraRotation = false;


	static ConstructorHelpers::FObjectFinder<UInputAction> MouseInputActionMouse(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_CameraRotation_Mouse.IA_CameraRotation_Mouse'"));
	if (MouseInputActionMouse.Succeeded())
	{
		SetMouseRotation_XY = MouseInputActionMouse.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseInputActionClick(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_CameraRotation_Click.IA_CameraRotation_Click'"));
	if (MouseInputActionClick.Succeeded())
	{
		SetCameraRotationTouchAction = MouseInputActionClick.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> KeyboardInputForwardPress(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_MoveCamera_WS.IA_MoveCamera_WS'"));
	if (KeyboardInputForwardPress.Succeeded())
	{
		SetMoveCamera_WS = KeyboardInputForwardPress.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> KeyboardInputRightPress(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_MoveCamera_DA.IA_MoveCamera_DA'"));
	if (KeyboardInputRightPress.Succeeded())
	{
		SetMoveCamera_DA = KeyboardInputRightPress.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> KeyboardInputUpDownPress(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_MoveUpDown_QE.IA_MoveUpDown_QE'"));
	if (KeyboardInputUpDownPress.Succeeded())
	{
		SetMoveCamera_QE = KeyboardInputUpDownPress.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseInputPlacementClick(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_Placement_Click.IA_Placement_Click'"));
	if (MouseInputPlacementClick.Succeeded())
	{
		SetPlacement_MouseClick = MouseInputPlacementClick.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> KeyboardCTRLHold(TEXT("/Script/EnhancedInput.InputAction'/Game/TopDown/Input/Actions/IA_CTRL_Hold.IA_CTRL_Hold'"));
	if (KeyboardCTRLHold.Succeeded())
	{
		TriggerCTRL_Keyboard = KeyboardCTRLHold.Object;
	}

}

void AcityBuilderPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//bShowMouseCursor = false;


	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	//bShowMouseCursor = true;
	APawn* ControlledPawn = GetPawn();
	//ControlledPawnGetCharacterMovement()->SetMovementMode(MOVE_Flying);

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;





	AHUD* myHUD = GetHUD();
	
	gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));


	
	
	
}

void AcityBuilderPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector HitLocation;
	GetCursorProjection(HitLocation);
}



void AcityBuilderPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	bShowMouseCursor = false;	


	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//EnhancedInputComponent->BindAction(SetMouseRotation_XY, ETriggerEvent::Started, this, &AcityBuilderPlayerController::Look);
		EnhancedInputComponent->BindAction(SetMouseRotation_XY, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::Look);
		EnhancedInputComponent->BindAction(SetMoveCamera_WS, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::MoveCamera_WS);
		EnhancedInputComponent->BindAction(SetMoveCamera_DA, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::MoveCamera_DA);
		EnhancedInputComponent->BindAction(SetMoveCamera_QE, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::MoveCamera_QE);


		// Setup mouse input events
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AcityBuilderPlayerController::OnInputStarted);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::OnSetDestinationTriggered);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AcityBuilderPlayerController::OnSetDestinationReleased);
		//EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AcityBuilderPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AcityBuilderPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AcityBuilderPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AcityBuilderPlayerController::OnTouchReleased);

		// Setup touch input events
		//EnhancedInputComponent->BindAction(SetCameraRotationTouchAction, ETriggerEvent::Started, this, &AcityBuilderPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetCameraRotationTouchAction, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::OnCameraRotationTriggered);
		EnhancedInputComponent->BindAction(SetCameraRotationTouchAction, ETriggerEvent::Completed, this, &AcityBuilderPlayerController::OnCameraRotationReleased);
		EnhancedInputComponent->BindAction(SetCameraRotationTouchAction, ETriggerEvent::Canceled, this, &AcityBuilderPlayerController::OnCameraRotationReleased);

		
		EnhancedInputComponent->BindAction(SetPlacement_MouseClick, ETriggerEvent::Started, this, &AcityBuilderPlayerController::OnPlacementStarted);

		EnhancedInputComponent->BindAction(TriggerCTRL_Keyboard, ETriggerEvent::Triggered, this, &AcityBuilderPlayerController::OnCTRLTriggered);
		EnhancedInputComponent->BindAction(TriggerCTRL_Keyboard, ETriggerEvent::Canceled, this, &AcityBuilderPlayerController::OnCTRLCanceled);


	

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AcityBuilderPlayerController::OnInputStarted()
{
	StopMovement();
}



// Triggered every frame when the input is held down
void AcityBuilderPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AcityBuilderPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AcityBuilderPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AcityBuilderPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AcityBuilderPlayerController::OnPlacementStarted()
{
	AUIManager* uiManager = gameManager->uiManager;
	uiManager->TestInput();
}





void AcityBuilderPlayerController::OnCTRLTriggered()
{
	AUIManager* uiManager = gameManager->uiManager;
	uiManager->ctrlHeld = true;
}
void AcityBuilderPlayerController::OnCTRLCanceled()
{
	AUIManager* uiManager = gameManager->uiManager;
	uiManager->ctrlHeld = false;
}

// RIGHT MOUSE INPUT ACTION EVENTS
void AcityBuilderPlayerController::OnCameraRotationTriggered() 
{
	UE_LOG(LogTemplateCharacter, Error, TEXT("on camera trigger"), *GetNameSafe(this));
	allowCameraRotation = true;


}

void AcityBuilderPlayerController::OnCameraRotationReleased()
{
	UE_LOG(LogTemplateCharacter, Error, TEXT("on camera trigger"), *GetNameSafe(this));
	allowCameraRotation = false;

}
	
void AcityBuilderPlayerController::Look(const FInputActionValue& ActionValue)
{
	if (allowCameraRotation)
	{
		const FVector2D AxisValue = ActionValue.Get<FVector2D>();
		UE_LOG(LogTemplateCharacter, Log, TEXT("X: %f, Y: %f"), AxisValue.X, AxisValue.Y);
		USpringArmComponent* MyCameraBoom = Cast<USpringArmComponent>(GetPawn()->GetComponentByClass(USpringArmComponent::StaticClass()));


		APawn* ControlledPawn = GetPawn();
		if (MyCameraBoom)
		{
			//UE_LOG(LogTemplateCharacter, Warning, TEXT("Mouse Location: %f, %f"), mouseX, mouseY);
			FRotator NewRotation = MyCameraBoom->GetRelativeRotation();
			NewRotation.Yaw += AxisValue.X;    // Adjust as necessary for sensitivity
			NewRotation.Pitch += AxisValue.Y; // Adjust as necessary for sensitivity or to limit pitch values

			MyCameraBoom->SetRelativeRotation(NewRotation);
		}
	}
	
}

void AcityBuilderPlayerController::MoveCamera_WS(const FInputActionValue& Value)
{
	// Move towards direction
	USpringArmComponent* MyCameraBoom = Cast<USpringArmComponent>(GetPawn()->GetComponentByClass(USpringArmComponent::StaticClass()));
	APawn* ControlledPawn = GetPawn();
	if (MyCameraBoom != nullptr && ControlledPawn != nullptr)
	{
		FVector camForward = MyCameraBoom->GetForwardVector();
		ControlledPawn->AddMovementInput(camForward, Value.GetMagnitude(), false);
	}
}

void AcityBuilderPlayerController::MoveCamera_DA(const FInputActionValue& Value)
{
	// Move towards direction
	USpringArmComponent* MyCameraBoom = Cast<USpringArmComponent>(GetPawn()->GetComponentByClass(USpringArmComponent::StaticClass()));
	APawn* ControlledPawn = GetPawn();
	if (MyCameraBoom != nullptr && ControlledPawn != nullptr)
	{
		FVector camRight = MyCameraBoom->GetRightVector();
		ControlledPawn->AddMovementInput(camRight, Value.GetMagnitude(), false);
	}
}

void AcityBuilderPlayerController::MoveCamera_QE(const FInputActionValue& Value)
{
	USpringArmComponent* MyCameraBoom = Cast<USpringArmComponent>(GetPawn()->GetComponentByClass(USpringArmComponent::StaticClass()));
	APawn* ControlledPawn = GetPawn();
	if (MyCameraBoom != nullptr && ControlledPawn != nullptr)
	{
		FVector camUp = MyCameraBoom->GetUpVector();
		//FVector UpVector = FVector::UpVector * Value.GetMagnitude();
		//ControlledPawn->AddMovementInput(camUp, Value.GetMagnitude(), false);
		ControlledPawn->AddActorWorldOffset(camUp, false);
	}
}

void AcityBuilderPlayerController::GetCursorProjection(FVector& OutLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	float MousePositionX, MousePositionY;
	if (GetMousePosition(MousePositionX, MousePositionY))
	{
		// Convert the 2D cursor position to a 3D world position and directio
		FVector WorldLocation, WorldDirection;
		//if (DeprojectScreenPositionToWorld(MousePositionX / ViewportSizeX, MousePositionY / ViewportSizeY, WorldLocation, WorldDirection))

		if (DeprojectScreenPositionToWorld(MousePositionX, MousePositionY , WorldLocation, WorldDirection))
		{
			//FVector VectorMousePosition(MousePositionX, MousePositionY, 0.0f);
			//if (GEngine)
			//{
			//	
			//	// Print the FVector to the screen
			//	GEngine->AddOnScreenDebugMessage(
			//		-1,        // Key (or -1 for no key and therefore no need to worry about overwriting previous messages)
			//		5.0f,      // Display duration in seconds
			//		FColor::Green, // Color of the text
			//		FString::Printf(TEXT("Projected Mouse Position: %s"), *VectorMousePosition.ToString()) // The text to display
			//	);
			//	GEngine->AddOnScreenDebugMessage(
			//		-1,        // Key (or -1 for no key and therefore no need to worry about overwriting previous messages)
			//		5.0f,      // Display duration in seconds
			//		FColor::Red, // Color of the text
			//		FString::Printf(TEXT("Projected Mouse Position: %s"), *WorldLocation.ToString()) // The text to display
			//	);
			//	GEngine->AddOnScreenDebugMessage(
			//		-1,        // Key (or -1 for no key and therefore no need to worry about overwriting previous messages)
			//		5.0f,      // Display duration in seconds
			//		FColor::Yellow, // Color of the text
			//		FString::Printf(TEXT("Projected Mouse Position: %s"), *WorldDirection.ToString()) // The text to display
			//	);
			//}
			// Perform a line trace from the cursor position into the world
			FHitResult HitResult;
			FVector Start = WorldLocation;
			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SpawnResident timer: %f"), Start.X));*/
			FVector End = Start + (WorldDirection * 100000);
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);
			//CollisionParams.AddIgnoredActor(GetPawn());
			
			// Line trace for visibility channel or specific object type, depending on what you want to hit
			if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::LANDSCAPE, CollisionParams))
			{
				
				OutLocation = HitResult.Location;
				
				//GEngine->AddOnScreenDebugMessage(
				//	-1,        // Key (or -1 for no key and therefore no need to worry about overwriting previous messages)
				//	1.0f,      // Display duration in seconds
				//	FColor::Blue, // Color of the text
				//	FString::Printf(TEXT("Projected Mouse Position: %s"), *HitResult.ImpactPoint.ToString()) // The text to display
				//);
				//GEngine->AddOnScreenDebugMessage(
				//	-1,        // Key (or -1 for no key and therefore no need to worry about overwriting previous messages)
				//	1.0f,      // Display duration in seconds
				//	FColor::Purple, // Color of the text
				//	FString::Printf(TEXT("Projected Mouse Position: %s"), *HitResult.ToString()) // The text to display
				//);
				return;
			}
		}
	}

	OutLocation = FVector::ZeroVector;
}


