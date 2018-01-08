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
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	AActor *Owner = GetOwner();
	FString ObjectName = GetOwner()->GetName();

	FRotator ObjectRotation = FRotator(0.0f, 90.0f, 0.0f);

	Owner->SetActorRotation(ObjectRotation, ETeleportType::None);

	FString ObjectRotationString = GetOwner()->GetActorRotation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s."), *ObjectName, *ObjectRotationString);
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
	}
}

