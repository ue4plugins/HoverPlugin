// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "SimpleCodeHoverComponent.generated.h"


/**
 * This class implements a component that can be attached to a movable
 * primitive component in order to give it hovering physics. It is a direct
 * conversion of the BlueprintHoverComponent to C++.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOVERPLUGIN_API USimpleCodeHoverComponent
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
	USimpleCodeHoverComponent();

public:

	// UComponent interface

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	/** Initialize the primitive component that owns this hover component. */
	void InitializePrimitiveComponent();

private:

	/** The primitive component that should hover. */
	UPROPERTY()
	UPrimitiveComponent* PrimitiveComponent;
};
