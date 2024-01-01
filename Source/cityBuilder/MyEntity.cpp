// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEntity.h"
#include "GameManager.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
AMyEntity::AMyEntity()
{
 	
   
}

// Called when the game starts or when spawned
void AMyEntity::InitEntity(EEntityType type, AGameManager* gm)
{
    //gameManager = gm;
    ////gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
    //if (gameManager != nullptr)
    //{
    //    entityHandle = gameManager->myEntityManager->SpawnEntity(type);
    //}
    //UE_LOG(LogTemp, Warning, TEXT("InitEntity: %f"), entityHandle.typeNum);
}

// Called every frame
void AMyEntity::UpdateEntity(float deltaTime)
{
	
}
