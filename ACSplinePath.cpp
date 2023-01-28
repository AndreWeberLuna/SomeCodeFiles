// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSplinePath.h"
#include "DTBezier.h"

#define HANDLE_SCALE 3.0f

UACSplinePath::UACSplinePath()
{
	// bAllowDiscontinuousSpline = true;
}

/*
#if WITH_EDITOR
void UACSplinePath::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UACSplinePath, PathDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Table was changed"));
		CreateSplinePoints();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
*/

void UACSplinePath::CreateSplinePoints()
{
	ClearSplinePoints(true);

	if (ensure(PathDataTable != nullptr))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Table was found"));
		const FString ContextString = "Bezier Data Table";
		TArray<FDTBezier*> Rows;

		PathDataTable->GetAllRows<FDTBezier>(ContextString, Rows);

		for (int i = 0; i < Rows.Num(); i++)
		{
			const FVector BezierPointCoord = FVector((*Rows[i]).px, (*Rows[i]).py, (*Rows[i]).pz);
			const FVector PointLocation = BezierPointCoord;

			AddSplinePoint(PointLocation, ESplineCoordinateSpace::Local);

			const FVector BezierLeftHandleCoord = FVector((*Rows[i]).hlx, (*Rows[i]).hly, (*Rows[i]).hlz);
			const FVector BezierRightHandleCoord = FVector((*Rows[i]).hrx, (*Rows[i]).hry, (*Rows[i]).hrz);
			const FVector LeftTangent = (PointLocation - BezierLeftHandleCoord) * HANDLE_SCALE;
			const FVector RightTangent = (BezierRightHandleCoord - PointLocation) * HANDLE_SCALE;

			SetTangentsAtSplinePoint(i, LeftTangent, RightTangent, ESplineCoordinateSpace::World, true);
			SetSplinePointType(i, ESplinePointType::Linear);
			SetSplinePointType(i, ESplinePointType::Curve);
		}
	}
}