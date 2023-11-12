// Copyright Yenum dot dev


#include "Rooms/PCGRoom.h"

// Sets default values
APCGRoom::APCGRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Rectangle.X0 = 0;
	Rectangle.X1 = 4;
	Rectangle.Y0 = 0;
	Rectangle.Y1 = 6;
	Width = Rectangle.X1 - Rectangle.X0;
	Length = Rectangle.Y1 - Rectangle.Y0;
	ShorterSide = FMath::Abs(Width) < FMath::Abs(Length) ? Width : Length;
	Area = Width * Length;
}

float APCGRoom::SumChildrenAreas()
{
	// Recursion through children nodes
	float Sum = Area;
	for (APCGRoom* Child: RoomChildren)
	{
		Sum += Child->SumChildrenAreas();
	}
	return Sum;
}

float APCGRoom::MaxChildrenValue()
{
	// Recursion through children nodes
	float Max = Area;
	for (APCGRoom* Child: RoomChildren)
	{
		if(const float ChildMax = Child->MaxChildrenValue(); ChildMax > Max)
		{
			Max = ChildMax;
		}
	}
	return Max;
}

float APCGRoom::MinChildrenValue()
{
	// Recursion through children nodes
	float Min = Area;
	for (APCGRoom* Child: RoomChildren)
	{
		if(const float ChildMin = Child->MinChildrenValue(); ChildMin < Min)
		{
			Min = ChildMin;
		}
	}
	return Min;
}

/**
 * @brief
 * @return max ((ShorterSide^2 * MaxRow)/SumRow^2,(SumRow^2/(ShorterSide^2 * MinRow))
 */
float APCGRoom::MaxAspectRatioInRow()
{
	TArray<float> ValueInRow = this->GetArrayOfChildrenAreas();
	// Add the current Area to Value In Row
	ValueInRow.Add(Area);
	
	// get Min in Row
	const float MinRow = FMath::Min(ValueInRow);
	// get Max in Row
	const float MaxRow = FMath::Max(ValueInRow);
	// get Sum in Row
	const float SumRow = SumFloat(ValueInRow);
	const float ShorterSideSquared = ShorterSide * ShorterSide;
	const float SumRowSquared = SumRow * SumRow;
	const float LeftCalc = (ShorterSideSquared * MaxRow)/SumRowSquared;
	const float RightCalc = SumRowSquared/(ShorterSideSquared * MinRow);
	return FMath::Max(LeftCalc, RightCalc);
}

void APCGRoom::FitRowIntoContainer(const TArray<float>& ChildrenAreaArray, FLayout Container)
{
	const float AbsWidth = FMath::Abs(Container.X1 - Container.X0);
	const float AbsLength = FMath::Abs(Container.Y1 - Container.Y0);
	const float ChildrenAreaSum = SumFloat(ChildrenAreaArray);
	const float ContainerArea = AbsWidth * AbsLength;

	const float OccupiedFraction = ChildrenAreaSum / ContainerArea;

	if (AbsWidth <= AbsLength)
	{
		const float NewY1 = Container.Y1 - OccupiedFraction * AbsLength;
		float CurrentY1 = NewY1;
		// Lay out the children vertically along the shorter side of the container
		for (APCGRoom* Child : RoomChildren)
		{
			const float ChildArea = Child->Area;
			const float ChildLength = ChildArea / ChildrenAreaSum * AbsLength;
			const FLayout NewRectangle = {
				Container.X0,
				CurrentY1 - ChildLength,
				Container.X1,
				CurrentY1
			};
			Child->Rectangle = NewRectangle;
			Child->Width = Child->Rectangle.X1 - Child->Rectangle.X0;
			Child->Length = Child->Rectangle.Y1 - Child->Rectangle.Y0;
			Child->ShorterSide = FMath::Abs(Child->Width) < FMath::Abs(Child->Length) ? Width : Length;
			Child->Area = Child->Width * Child->Length;
			// Update CurrentY1 for the next child
			CurrentY1 -= ChildLength;
			// Recursively call FitRowIntoContainer for the child
			// Child->FitRowIntoContainer(Child->GetArrayOfChildrenAreas(), Child->Rectangle);
		}
	}
	else
	{
		const float NewX1 = Container.X0 + OccupiedFraction * AbsWidth;
		float CurrentX0 = NewX1;

		// Lay out the children horizontally along the shorter side of the container
		for (APCGRoom* Child : RoomChildren)
		{
			const float ChildArea = Child->Area;
			const float ChildWidth = ChildArea / ChildrenAreaSum * AbsWidth;
			const FLayout NewRectangle = {
				CurrentX0,
				Container.Y0,
				CurrentX0 + ChildWidth,
				Container.Y1
			};
			// Update the child rectangle
			Child->Rectangle = NewRectangle;

			// Update CurrentX0 for the next child
			CurrentX0 += ChildWidth;

			// Recursively call FitRowIntoContainer for the child
			// Child->FitRowIntoContainer(Child->GetArrayOfChildrenAreas(), Child->Rectangle);
		}
	}
}


TArray<float> APCGRoom::GetArrayOfChildrenAreas()
{
	TArray<float> ValueInRow;
	// Assuming 'Children' is an array of UPCGRoom objects
	for (const APCGRoom* Room : RoomChildren)
	{
		if (Room)
		{
			// Assuming 'Area' is a property in the UPCGRoom class
			float RoomArea = Room->Area;
			ValueInRow.Add(RoomArea);
		}
	}
	return ValueInRow;
}

float APCGRoom::SumFloat(const TArray<float>& Numbers)
{
	float Sum = 0;
	for (const float Number : Numbers)
	{
		Sum += Number;
	}
	return Sum;
}

int APCGRoom::SumInt(const TArray<int>& Numbers)
{
	int Sum = 0;
	for (const int Number : Numbers)
	{
		Sum += Number;
	}
	return Sum;
}

// Called when the game starts or when spawned
void APCGRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

