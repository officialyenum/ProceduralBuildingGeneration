// Copyright Yenum dot dev


#include "PCGBuildingGenerator.h"

// Sets default values
APCGBuildingGenerator::APCGBuildingGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GenerateBuildingLayout();

}

void APCGBuildingGenerator::GenerateBuildingLayout()
{
	check(RoomRootNode);
	GenerateLayoutWithSquarifiedAlgo(RoomRootNode);
}

void APCGBuildingGenerator::GenerateLayoutWithSquarifiedAlgo(APCGRoom* CurrentRoomNode)
{
	if(!CurrentRoomNode)
	{
		return;
	}
	if(CurrentRoomNode && CurrentRoomNode->RoomChildren.IsEmpty())
	{
		// if no children nodes recurse null
		GenerateLayoutWithSquarifiedAlgo(nullptr);
		return;
	}
	// room node exists and has children
	CurrentRoomNode->FitRowIntoContainer(CurrentRoomNode->GetArrayOfChildrenAreas(), CurrentRoomNode->Rectangle);
	for (APCGRoom* Room : CurrentRoomNode->RoomChildren)
	{
		GenerateLayoutWithSquarifiedAlgo(Room);
	}
}

// Called when the game starts or when spawned
void APCGBuildingGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

