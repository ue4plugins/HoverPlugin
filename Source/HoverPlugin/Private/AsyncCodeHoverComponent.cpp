// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverPluginPrivatePCH.h"
#include "AsyncCodeHoverComponent.h"
#include "DrawDebugHelpers.h"


UAsyncCodeHoverComponent::UAsyncCodeHoverComponent()
	: MaxHoverForce(10000.0f)
	, MaxHoverForceDistance(200.0f)
	, PrimitiveComponent(nullptr)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAsyncCodeHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	// For better readability and reusability, we moved the initialization
	// code for the primitive component into a separate function (see below).

	InitializePrimitiveComponent();
}


// Called every frame
void UAsyncCodeHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PrimitiveComponent == nullptr)
	{
		return;
	}

	const FVector Start = ComponentToWorld.GetLocation();
	const FVector End = FVector(Start.X, Start.Y, -MaxHoverForceDistance);

	// One drawback of the line trace implementation in USimpleCodeHoverComponent
	// is that the trace takes place on the precious game thread. Traces are not
	// prohibitively expensive, but also not exactly cheap. It would be better if
	// we could offload this work to another thread. We can accomplish this using
	// so called asynchronous line traces.

	// Asynchronous line traces consist of two parts: queueing the desired trace
	// operation, and reading back the resulting data when the trace is complete.
	// Asynchronous traces do not complete right away. For simplicity, we will
	// process the results in the next tick. This means that our traces are one
	// frame off, but for something like a hover effect this does not matter.

	// In order to not overwrite the asynchronous trace handle returned from the
	// previous trace, we first process the trace results of the last frame.

	FTraceDatum TraceDatum;

	if (World->QueryTraceData(AsyncTrace, TraceDatum))
	{
		if (TraceDatum.OutHits.Num() > 0)
		{
			const FHitResult& HitResult = TraceDatum.OutHits[0];

			const float Distance = (Start - HitResult.ImpactPoint).Size();
			const float Ratio = Distance / MaxHoverForceDistance;
			const FVector Force = (1.0f - FMath::Clamp(Ratio, 0.0f, 1.0f)) * MaxHoverForce * HitResult.ImpactNormal;

			// Previously, we treated the force as is. Now we interpret it as an
			// acceleration instead. The latter has the advantage that the force
			// will become independent of the component's mass, so that our code
			// will still work if we scale up our hovering Actor in the Editor.

			PrimitiveComponent->AddForce(Force, NAME_None, true);

			::DrawDebugLine(World, Start, End, FColor::Red, false, 0.0f);
			::DrawDebugPoint(World, HitResult.ImpactPoint, 16.0f, FColor::Red, false, 0.0f);
		}
	}

	// Now that the previous frame's results are processed, we can issue a new trace.
	// The new returned trace handle will be used in the tick of the next frame.

	AsyncTrace = World->AsyncLineTraceByChannel(Start, End, ECC_WorldDynamic, FCollisionQueryParams(TEXT("AsyncHoverTrace")));
}


void UAsyncCodeHoverComponent::OnAttachmentChanged()
{
	// The USimpleCodeHoverComponent implementation has the disadvantage that
	// it does not support re-attaching this hover component to different
	// parent components. We cannot guarantee that this will never happen, so
	// we should not rely on the assumption that it won't. This function is
	// called each time this hover component is attached to a different parent.
	// We use it to reinitialize the new parent component.

	InitializePrimitiveComponent();
}


void UAsyncCodeHoverComponent::InitializePrimitiveComponent()
{
	// Instead of getting the parent component via the owning actor's root
	// component, we can shorten the code by using the 'AttachParent' member
	// of 'SceneComponent', which already caches this pointer.

	PrimitiveComponent = Cast<UPrimitiveComponent>(AttachParent);

	if (PrimitiveComponent != nullptr)
	{
		PrimitiveComponent->SetSimulatePhysics(true);
		PrimitiveComponent->SetLinearDamping(2.0f);
		PrimitiveComponent->SetAngularDamping(2.0f);
	}
}
