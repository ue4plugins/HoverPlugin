// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/SceneComponent.h"
#include "UObject/ObjectMacros.h"
#include "WorldCollision.h"

#include "AsyncCodeHoverComponent.generated.h"


/**
 * This class implements a component that can be attached to a movable
 * primitive component in order to give it hovering physics. It is similar
 * to USimpleCodeHoverComponent, but improves some of the code for better
 * performance. In particular, the following improvements have been made:
 *
 * - The line traces no longer happen on the game thread, but asynchronously
 * - Added support for reattaching our hover component to other parents
 * - Made the hover effect independent of the hovering actor's scale (and mass)
 * - Shortened and reformatted some of the code to be more readable
 *
 * See the code comments for an explanation of the changes.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOVERPLUGIN_API UAsyncCodeHoverComponent
	: public USceneComponent
{
	GENERATED_BODY()

	/** The maximum hover force to apply. */
	UPROPERTY(EditAnywhere, Category="Hover")
	float MaxHoverForce;

	/** The maximum distance at which the hover force applies. */
	UPROPERTY(EditAnywhere, Category="Hover")
	float MaxHoverForceDistance;

public:

	/** Create and initialize a new instance. */
	UAsyncCodeHoverComponent();

public:

	//~ UComponent interface

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	//~ USceneComponent interface

	virtual void OnAttachmentChanged() override;

protected:

	/** Initialize the primitive component that owns this hover component. */
	void InitializePrimitiveComponent();

private:

	/** The primitive component that should hover. */
	UPROPERTY()
	UPrimitiveComponent* PrimitiveComponent;

	/** Handle for retrieving asynchronous line trace results. */
	FTraceHandle AsyncTrace;
};
