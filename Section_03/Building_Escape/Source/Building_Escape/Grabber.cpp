// (C) 2017 Charles Unruh

#include "Grabber.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab()
{
	
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physics Handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber]{%s}<Missing Component> NO PHYSICS HANDLE COMPONENT FOUND ON OBJECT!"), *(GetOwner()->GetName()));
	}

	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		///Input is found
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber]{%s}<Missing Component> NO INPUT COMPONENT FOUND ON OBJECT!"), *(GetOwner()->GetName()));
	}

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	/// get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	//UE_LOG(LogTemp, Warning, TEXT("[Grabber]{%s} Position: <%s> Rotation: <%s>"), *(GetOwner()->GetName()), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.ToString()));

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0, 128), true, 10.0f, 0, 1.0f);

	/// ray-cast to reach distance
	FCollisionQueryParams TraceParameters(FName(TEXT("")), true, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	///see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Grabber]{%s} Trace Hit: %s"), *(GetOwner()->GetName()), *(ActorHit->GetName()));
	}
}

