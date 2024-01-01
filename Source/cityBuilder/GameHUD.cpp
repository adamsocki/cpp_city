// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "UObject/ConstructorHelpers.h"



AGameHUD::AGameHUD()
{

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("WidgetBlueprint'/Game/TopDown/Blueprints/UI/BP_UIWidget.BP_UIWidget_C'"));
    if (WidgetClassFinder.Succeeded())
    {
        GameWidgetClass = WidgetClassFinder.Class;
    }
    for (int i = 0; i < 10; i++)
    {

        UE_LOG(LogTemp, Warning, TEXT("Hello"));
    }
    if (GameWidgetClass != nullptr)
    {
        // Create the widget and add it to the viewport
        GameWidget = Cast<UUserWidget>(CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass));
        if (GameWidget)
        {

            GameWidget->AddToViewport();
        }
    }
}


void AGameHUD::BeginPlay()
{
    
    if (GameWidgetClass != nullptr)
    {
        // Create the widget and add it to the viewport
        GameWidget = Cast<UUserWidget>(CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass));
        if (GameWidget)
        {
            
            GameWidget->AddToViewport();
        }
    }
    

}
