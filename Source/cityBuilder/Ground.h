// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ground.generated.h"

UCLASS()
class CITYBUILDER_API AGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GroundMesh;


};
