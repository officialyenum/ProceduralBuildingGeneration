// Copyright Yenum dot dev

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ERoomType : uint8
{
	LivingRoom UMETA(DisplayName = "Living Room"),
	MasterBedroom UMETA(DisplayName = "MasterBedroom"),
	Bedroom UMETA(DisplayName = "Bedroom"),
	Kitchen UMETA(DisplayName = "Kitchen"),
	Bathroom UMETA(DisplayName = "Bathroom"),
	Toilet UMETA(DisplayName = "Toilet"),
};

USTRUCT(BlueprintType)
struct FLayout
{
	float X0;
	float X1;
	float Y0;
	float Y1;
};

UCLASS()
class PCG_BUILDING_API UPCGRoom: public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintReadWrite, EditAnywhere, Category="EDIT ROOM PARAMS")
	FLayout Rectangle;
	
	UFUNCTION(BlueprintReadWrite, EditAnywhere, Category="EDIT ROOM PARAMS")
	ERoomType Type;
	
	UFUNCTION(BlueprintReadWrite, EditAnywhere, Category="EDIT ROOM PARAMS")
	TArray<UPCGRoom*> Children;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Width;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Breadth;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Area;

	UPROPERTY(BlueprintReadOnly)
	float ShorterSide;

	float SumChildrenValues();
	
	float MaxChildrenValue();
	
	float MinChildrenValue();
	
	float MaxAspectRatioInRow();
	
	float FitRowIntoContainer();

	
	TArray<float> GetArrayOfChildrenAreas();
	
	UPCGRoom();
	
	UPCGRoom(FLayout Rectangle, const ERoomType Type);
	
	~UPCGRoom();
	
private:
	static float SumFloat(const TArray<float>& Numbers);
	static int SumInt(const TArray<int>& Numbers);
};
