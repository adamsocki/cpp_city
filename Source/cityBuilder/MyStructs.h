
#pragma once

#include "CoreMinimal.h"
#include "MyStructs.generated.h"


UENUM(BlueprintType)
enum class EGameMode : uint8
{
    GameMode_Editor1,
    GameMode_Editor2,

    GameMode_Count
};


UENUM(BlueprintType)
enum class EControllerState : uint8
{
    ControllerState_GamePlay,
    ControllerState_OverButton,
    ControllerState_Placement,

    ControllerState_None
};


UENUM(BlueprintType)
enum class EEntityType : uint8
{
    EntityType_Resident,
    EntityType_PortOfEntry,
    EntityType_Building,

    EntityType_Count,
};

UENUM(BlueprintType)
enum class EAgencyType : uint8
{
    AgencyType_Placement,

    AgencyType_Count
};

UENUM(BlueprintType)
enum class EResidentState : uint8
{
    ResidentState_Moving,
    ResidentState_Idle,
    ResidentState_Idle_NoUpdate,
    ResidentState_Active,
    ResidentState_Assignment,

    ResidentState_Count
};


UENUM(BlueprintType)
enum class EAssingmentType : uint8
{
    AssingmentType_ToHome,

    

    AssingmentType_Count
};


USTRUCT(BlueprintType)
struct FEntityHandle
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityHandle Struct")
    int32 generation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityHandle Struct")
    int32 indexInInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My First Struct")
    EEntityType type;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My First Struct")
    int32 typeNum;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My First Struct")
    bool isInit;
};

USTRUCT(BlueprintType)
struct FMyEntityInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityInfo Struct")
    int32 generation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityInfo Struct")
    int32 indexInBuffer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityInfo   Struct")
    EEntityType type;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityInfo   Struct")
    int32 typeNum;
};


USTRUCT(BlueprintType)
struct FEntityTypeBuffer
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityTypeBuffer Struct")
    int32 count;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityTypeBuffer Struct")
    int32 capacity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityTypeBuffer Struct")
    int32 sizeInBytes;

    //UPROPERTY( BlueprintReadWrite, Category = "My FEntityTypeBuffer Struct")
    void* entities;

    //TArray<AMyEntity>* entitiesArray;
};




USTRUCT(BlueprintType)
struct FEntityManager {
   GENERATED_BODY()
    
public:
    FEntityTypeBuffer* buffers;
    FMyEntityInfo* entities;
    int32 entityCapacity;

    int32 nextID;

    TArray<EEntityType> entityTypes;
};



USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_BODY()
public:
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My FEntityHandle Struct")
    FEntityManager em;

    /*FEntityInfo* entities;
    FEntityTypeBuffer* buffers;*/
    TArray<AActor*> buildingActors;
};