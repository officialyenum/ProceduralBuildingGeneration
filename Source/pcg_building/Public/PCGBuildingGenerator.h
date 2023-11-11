// Copyright Yenum dot dev

#pragma once

#include "CoreMinimal.h"
#include "Rooms/PCGRoom.h"

/**
 * 
 */
UCLASS()
class PCG_BUILDING_API UPCGBuildingGenerator: public UObject
{
	
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPCGRoom* RoomRootNode;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Area;
	
	UPCGBuildingGenerator();
	UFUNCTION(BlueprintCallable, Category="Building Generator")
	void GenerateBuildingLayout();
	
	UFUNCTION(BlueprintCallable, Category="Building Generator")
	void GenerateLayoutWithSquarifiedAlgo(UPCGRoom* CurrentRoomNode);
	~UPCGBuildingGenerator();
};
