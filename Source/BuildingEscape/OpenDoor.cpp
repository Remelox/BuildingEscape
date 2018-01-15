// Copyright Adam R. McConnell 2018

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
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
}

void UOpenDoor::OpenDoor()
{
	FString ObjectName = GetOwner()->GetName();

	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f), ETeleportType::None);

	FString ObjectRotationString = GetOwner()->GetActorRotation().ToString();

	//UE_LOG(LogTemp, Warning, TEXT("%s is at %s."), *ObjectName, *ObjectRotationString);

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

	float TriggerMass = 30.f;

	if (GetTotalMassOfActorsOnPlate()>TriggerMass)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	TArray<AActor*> OverlappingActors;
	float TotalMass = 0.f;

	// Find all the overlapping actors. 
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor : OverlappingActors)
	{
		//Actor->GetName();
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
	}
	// Iterate through them adding their masses. 

	return TotalMass;
}

