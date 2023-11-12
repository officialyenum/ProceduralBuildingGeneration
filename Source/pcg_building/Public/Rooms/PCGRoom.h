// Copyright Yenum dot dev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCGRoom.generated.h"

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
	GENERATED_BODY()
	float X0;
	float X1;
	float Y0;
	float Y1;
};

UCLASS()
class PCG_BUILDING_API APCGRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCGRoom();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="EDIT ROOM PARAMS")
	FLayout Rectangle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="EDIT ROOM PARAMS")
	ERoomType Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="EDIT ROOM PARAMS")
	TArray<APCGRoom*> RoomChildren;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Width;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Length;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Area;

	UPROPERTY(BlueprintReadOnly)
	float ShorterSide;

	UFUNCTION(BlueprintCallable, Category="Room Functions")
	float SumChildrenAreas();
	
	UFUNCTION(BlueprintCallable, Category="Room Functions")
	float MaxChildrenValue();
	
	UFUNCTION(BlueprintCallable, Category="Room Functions")
	float MinChildrenValue();
	
	UFUNCTION(BlueprintCallable, Category="Room Functions")
	float MaxAspectRatioInRow();
	
	UFUNCTION(BlueprintCallable, Category="Room Functions")
	void FitRowIntoContainer(const TArray<float>& ChildrenAreaArray, FLayout NewRectangle);
	
	UFUNCTION(BlueprintCallable, Category="Room Functions")
	TArray<float> GetArrayOfChildrenAreas();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static float SumFloat(const TArray<float>& Numbers);
	static int SumInt(const TArray<int>& Numbers);
};
