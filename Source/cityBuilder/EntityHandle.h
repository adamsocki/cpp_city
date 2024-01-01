// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */



class CITYBUILDER_API EntityHandle
{
	
public:
	EntityHandle();
	~EntityHandle();

	int32 generation;
	int32 indexInInfo;

	//EntityType type;
};
