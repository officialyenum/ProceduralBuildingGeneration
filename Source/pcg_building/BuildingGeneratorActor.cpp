// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingGeneratorActor.h"

// Sets default values
ABuildingGeneratorActor::ABuildingGeneratorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	floors = 4;

}

// Called when the game starts or when spawned
void ABuildingGeneratorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingGeneratorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABuildingGeneratorActor::SetRoomsPerFloor()
{
	// This sets how many rooms wil be generated when creating the floor plan
};

void ABuildingGeneratorActor::GenerateFloor()
{
	// This generate a floor plan and raises the plan to roof level for another floor to be placed above or a roof
};

void ABuildingGeneratorActor::AddDoorsToFloor()
{
	// This is run after a floor plan is generated and generates doors for the floor
};

void ABuildingGeneratorActor::AddWindowsToFloor()
{

	// This is run after a floor plan and doors are generated and generates windows for the floor
	
};

void ABuildingGeneratorActor::AddRoofToLastFloor()
{

	// This checks if the generated floors is equal to the specified number of floors

};

