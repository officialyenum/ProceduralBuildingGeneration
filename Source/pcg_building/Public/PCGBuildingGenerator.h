// Copyright Yenum dot dev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rooms/PCGRoom.h"
#include "PCGBuildingGenerator.generated.h"

UCLASS()
class PCG_BUILDING_API APCGBuildingGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCGBuildingGenerator();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APCGRoom* RoomRootNode;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Area;
	
	UFUNCTION(BlueprintCallable, Category="Building Generator")
	void GenerateBuildingLayout();
	
	UFUNCTION(BlueprintCallable, Category="Building Generator")
	void GenerateLayoutWithSquarifiedAlgo(APCGRoom* CurrentRoomNode);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
