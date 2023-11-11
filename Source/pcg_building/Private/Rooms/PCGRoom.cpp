// Copyright Yenum dot dev


#include "Rooms/PCGRoom.h"

#include "DSP/Chorus.h"


float UPCGRoom::SumChildrenValues()
{
	// Recursion through children nodes
	float Sum = Area;
	for (UPCGRoom* Child: Children)
	{
		Sum += Child->SumChildrenValues();
	}
	return Sum;
}

float UPCGRoom::MaxChildrenValue()
{
	// Recursion through children nodes
	float Max = Area;
	for (UPCGRoom* Child: Children)
	{
		if(const float ChildMax = Child->MaxChildrenValue(); ChildMax > Max)
		{
			Max = ChildMax;
		}
	}
	return Max;
}

float UPCGRoom::MinChildrenValue()
{
	// Recursion through children nodes
	float Min = Area;
	for (UPCGRoom* Child: Children)
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
float UPCGRoom::MaxAspectRatioInRow()
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

float UPCGRoom::FitRowIntoContainer()
{
	const int AbsWidth = FMath::Abs(Width);
	const int AbsBreadth = FMath::Abs(Breadth);
	const float childrenAreaSum = SumFloat(GetArrayOfChildrenAreas());
	const int containerArea = AbsBreadth * AbsWidth;

	const float occupiedArea = childrenAreaSum / containerArea;
	if (AbsWidth <= AbsBreadth)
	{
		Rectangle.Y0 = Rectangle.Y1 - occupiedArea * AbsBreadth;
		for (UPCGRoom* Child: Children)
		{
			Child->FitRowIntoContainer();
		}
	}
	
	return 0;
}

UPCGRoom::UPCGRoom()
{
	Rectangle.X1 = 0;
	Rectangle.X0 = 0;
	Rectangle.Y0 = 0;
	Rectangle.Y1 = 0;
	Width = Rectangle.X1 - Rectangle.X0;
	Breadth = Rectangle.Y1 - Rectangle.Y0;
	ShorterSide = FMath::Abs(Width) < FMath::Abs(Breadth) ? Width : Breadth;
	Area = Width * Breadth;
}

UPCGRoom::UPCGRoom(FLayout Rectangle, const ERoomType Type) :
Rectangle(Rectangle),Type(Type)
{
	const float Width = Rectangle.X1 - Rectangle.X0;
	const float Breadth = Rectangle.Y1 - Rectangle.Y0;
	ShorterSide = FMath::Abs(Width) < FMath::Abs(Breadth) ? Width : Breadth;
	Area = Width * Breadth;
}

UPCGRoom::~UPCGRoom()
{
}

int UPCGRoom::SumInt(const TArray<int>& Numbers)
{
	int Sum = 0;
	for (const int Number : Numbers)
	{
		Sum += Number;
	}
	return Sum;
}

TArray<float> UPCGRoom::GetArrayOfChildrenAreas()
{
	TArray<float> ValueInRow;
	// Assuming 'Children' is an array of UPCGRoom objects
	for (const UPCGRoom* Room : Children)
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

float UPCGRoom::SumFloat(const TArray<float>& Numbers)
{
	float Sum = 0;
	for (const float Number : Numbers)
	{
		Sum += Number;
	}
	return Sum;
}
