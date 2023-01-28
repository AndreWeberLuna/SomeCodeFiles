// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "ACSplinePath.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUMPLINGDUELS_API UACSplinePath : public USplineComponent
{
	GENERATED_BODY()

public:

	// Class' constructor
	UACSplinePath();
	
	// Our data table containing the spline points
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* PathDataTable;

	// Function to convert the data table points to points of the spline
	UFUNCTION(BlueprintCallable, Category = "Programmer")
	void CreateSplinePoints();
/*
#if WITH_EDITOR
	// Function to fire if the component's variables are changed
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
*/

};
