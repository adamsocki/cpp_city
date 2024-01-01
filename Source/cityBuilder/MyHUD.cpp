// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

void AMyHUD::ClickTester()
{

	if (GEngine)
	{
		//building
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Dim[0] X:%.2f"), 3.32f));
	}
}
