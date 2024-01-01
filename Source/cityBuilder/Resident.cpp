// Fill out your copyright notice in the Description page of Project Settings.


#include "ResidentManager.h"
#include "buildingManager.h"

#include "Resident.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <NavigationSystem.h>

AResident::AResident()
{
    //ResidentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResidentMesh"));
    ResidentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResidentMesh"));
	RootComponent = ResidentMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
    if (MeshAsset.Succeeded())
    {
        ResidentMesh->SetStaticMesh(MeshAsset.Object);
        UE_LOG(LogTemp, Warning, TEXT("Loaded mesh for resident!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh for resident!"));
    }
    //// Set the collision profile name to "BlockAll" which blocks all channels by default
    //ResidentMesh->SetCollisionProfileName(TEXT("BlockAll"));
    ResidentMesh->SetGenerateOverlapEvents(true);

    //// Alternatively, set up individual collision responses
    //ResidentMesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //ResidentMesh->SetNotifyRigidBodyCollision(true); // To get hit events
    //ResidentMesh->BodyInstance.SetResponseToAllChannels(ECollisionResponse::ECR_Block); // Block all channels
    //ResidentMesh->BodyInstance.SetResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore); // Ignore camera

    //// Enable physics simulation if needed
    ////StaticMeshComponent->SetSimulatePhysics(true);
    //// In your actor's BeginPlay or constructor
    //ResidentMesh->OnComponentHit.AddDynamic(this, &AResident::OnHit);

     // Initialize the TriggerBox component
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    // Set the box component to trigger overlap events
    TriggerBox->SetGenerateOverlapEvents(true);
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    UStaticMesh* meshSize = ResidentMesh->GetStaticMesh();
    //meshSize->GetBounds().BoxExtent;
    TriggerBox->InitBoxExtent(meshSize->GetBounds().BoxExtent); // Set the size as needed
    // Attach the TriggerBox to the ResidentMesh
    TriggerBox->SetupAttachment(ResidentMesh);
    // Bind the overlap event
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AResident::OnOverlapBegin);

    inQueueTimer = 0.0f;

    residentLifecycle = CreateDefaultSubobject<UResidentLifecycle>("ResidentLifecycleComponent");
    wanderCount = 0;


}

void AResident::InitResident(APortOfEntry* portEntity)
{
    //spawnPort = portHandle;
    residentManager = Cast<AResidentManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AResidentManager::StaticClass()));
    // Load a static mesh from the content directory
    buildingManager = Cast<AbuildingManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AbuildingManager::StaticClass()));

    ////////////////
    /// STEP 0   ///
    ////////////////
    portEntity->residents.Add(this);

    ////////////////
    /// STEP 1   ///
    ////////////////
    //residentLifecycle->AssignToAgency();
    residentManager->RegisterResident(this);
    residentManager->AddToUpdateRoster(this);

    actorToMoveTo = buildingManager->ReturnNearestAgency(portEntity->GetActorLocation());

    if (actorToMoveTo)
    {
        residentState = EResidentState::ResidentState_Moving;
    }

    toUpdate = true;
    hasHome = false;

    movementSpeed = 775.0f;

    
    
}


//void AResident::ResidentLifecycle()
//{
//
//}


void AResident::UpdateResident(float deltaTime)
{
    if(residentState == EResidentState::ResidentState_Idle_NoUpdate)
    {
        residentManager->RemoveFromUpdateRoster(this);
    }

    if(ActorControllingResident != nullptr)
    {

    }
    switch(residentState)
    {
        case EResidentState::ResidentState_Idle:
        {

        }
        case EResidentState::ResidentState_Moving:
        {


            if (actorToMoveTo)
            {
                if (GEngine && hasHome)
                {
                   // FString actorToMoveToString = actorToMoveTo->GetName();
                   // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, actorToMoveToString);
                }


                MoveResidentToPlace(actorToMoveTo, deltaTime);

                FVector CurrentActorLocation = GetActorLocation();
                //FVector actorToMoveToLocation = actorToMoveTo->GetActorLocation();
               // FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CurrentActorLocation, actorToMoveToLocation);

                //float DistanceAwayFromDestination = FVector::Distance(CurrentActorLocation, actorToMoveToLocation);
                //if (DistanceAwayFromDestination <= 150.0f)
                //{
                //    TriggerBox->SetGenerateOverlapEvents(false);
                //    RemoveFromUpdateRoster();
                //   // agencyActor->AddResidentToQueue(this);
                //    residentState = EResidentState::ResidentState_Idle;
                //    isWandering = false;
                //    return;
                //}
            
            }
            else if (wanderCount > 3)
            {
                actorToMoveTo = buildingManager->ReturnNearestAgency(GetActorLocation());
                SetActorEnableCollision(true);
                isWandering = false;
                wanderCount = 1;
                TriggerBox->SetGenerateOverlapEvents(true);
            }
            else if (isWandering)
            {
                MoveResidentToLocation(destinationLocation, deltaTime);
                //UE_LOG(LogTemp, Warning, TEXT("isWandering"));

            }
        }
        default:
        {

        }
    }




}

void AResident::MoveSpecial(float deltaTime)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SpawnResident deltaTime: %f"), deltaTime ));
    FVector deltaLocation = FVector(100.0f, 1000.0f, 100.0f) * deltaTime;
    this->AddActorWorldOffset(deltaLocation);
}

void AResident::PrintWorking()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SpawnResident timer: %f"), 1.0f )); 

}


void AResident::MoveResidentToPlace(AActor* actor, float deltaTime)
{
    FVector CurrentActorLocation = GetActorLocation();
    FVector TargetActorLocation = actor->GetActorLocation();
        

    // Calculate the rotation needed to look at the target
    //FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CurrentActorLocation, TargetActorLocation);

    // Set the Actor's rotation
    //SetActorRotation(LookAtRotation);

    // Move towards the target Actor
    FVector Direction = (TargetActorLocation - CurrentActorLocation).GetSafeNormal();
    FVector NewLocation = CurrentActorLocation + (Direction * movementSpeed * deltaTime); // MoveSpeed is a float you define

    // Update the location
    SetActorLocation(NewLocation);
}

void AResident::MoveResidentToLocation(FVector location, float deltaTime)
{
    FVector CurrentActorLocation = GetActorLocation();
    //FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CurrentActorLocation, destinationLocation);
   
    float DistanceAwayFromDestination = FVector::Distance(CurrentActorLocation, destinationLocation);
    if (DistanceAwayFromDestination <= 10.0f)
    {
        AssignRandomWander();
        return;
    }
    // Set the Actor's rotation
    //SetActorRotation(LookAtRotation);

    // Move towards the target Actor
    FVector Direction = (destinationLocation - GetActorLocation()).GetSafeNormal();
    FVector NewLocation = GetActorLocation() + (Direction * movementSpeed * deltaTime); // MoveSpeed is a float you define

    // Update the location
    SetActorLocation(NewLocation);
}


void AResident::AddToUpdateRoster()
{
    residentManager->AddToUpdateRoster(this);
}

void AResident::RemoveFromUpdateRoster()
{
    residentManager->RemoveFromUpdateRoster(this);
    SetActorEnableCollision(false);

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("RemovedFromRoster %f"), 1.0f));

}

void AResident::RandomMoveLocation()
{



}

void AResident::AssignRandomWander()
{
    FVector RandomPoint;
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (NavSys)
    {
        FVector Origin = GetActorLocation(); // Some central point in your level, or the character's current location
        float Radius = 10000.0f; // How far from the origin you want to search, adjust as needed

        FNavLocation NavLocation;
        if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, NavLocation))
        {
            RandomPoint = NavLocation.Location;
        }
    }

    wanderCount++;
    isWandering = true;
    destinationLocation = RandomPoint;
    //UE_LOG(LogTemp, Warning, TEXT("MyVector: %s"), *destinationLocation.ToString());
    actorToMoveTo = nullptr;
    SetActorEnableCollision(false);
    //AddToUpdateRoster();

}

//void AResident::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//
//    if (GEngine)
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("HIT %f"), 1.0f));
//}

void AResident::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Handle the overlap event
    AAgency *agencyActor = Cast<AAgency>(OtherActor);

    if (OtherActor && (OtherActor != this) && agencyActor)
    {
        if (agencyActor->AcceptResident(this))
        {
            TriggerBox->SetGenerateOverlapEvents(false);
            RemoveFromUpdateRoster();
            agencyActor->AddResidentToQueue(this);
            isWandering = false;
        }
        else
        {
            AssignRandomWander();

        }
       
        return;
        // Log or handle your overlap event here
    }

    ABuilding* buildingActor = Cast<ABuilding>(OtherActor);
    FString ActorName = OtherActor->GetName();
    UE_LOG(LogTemp, Warning, TEXT("Name of OtherActor: %s"), *ActorName);
    
    if (OtherActor && (OtherActor != this) && buildingActor)
    {
        if (buildingActor == actorToMoveTo)
        {
            TriggerBox->SetGenerateOverlapEvents(false);

            RemoveFromUpdateRoster();
            //agencyActor->AddResidentToQueue(this);
            //buildingActor->current
            // @TODO: ADD RESIDENT TO CURRENTLY IN BUILDING->Building
            isWandering = false;
           // UE_LOG(LogTemp, Warning, TEXT("HIT DOOR"))
        }
        else
        {
            return;
        }
    }
}