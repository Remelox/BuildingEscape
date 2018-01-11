// Copyright Adam R. McConnell 2018

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	FString ObjectName = GetOwner()->GetName();

	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f), ETeleportType::None);

	FString ObjectRotationString = GetOwner()->GetActorRotation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s."), *ObjectName, *ObjectRotationString);

}

void UOpenDoor::CloseDoor()
{
	FString ObjectName = GetOwner()->GetName();

	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f), ETeleportType::None);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume 
	// If the ActorThatOpens is in the volume 
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

