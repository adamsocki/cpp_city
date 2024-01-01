// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadManager.h"
#include "GameManager.h"

// Sets default values
ASaveLoadManager::ASaveLoadManager()
{
}

void ASaveLoadManager::InitSaveLoadManager(AGameManager* gm)
{
	gameManager = gm;

	switch (gameManager->gameMode)
	{
		case EGameMode::GameMode_Editor1:
		{

		}
		case EGameMode::GameMode_Editor2:
		{

		}
		default:
		{

		}
	}
}

void ASaveLoadManager::UpdateSaveLoadManager()
{
}






