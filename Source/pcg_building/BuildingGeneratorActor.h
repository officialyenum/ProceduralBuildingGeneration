// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingGeneratorActor.generated.h"

UCLASS()
class PCG_BUILDING_API ABuildingGeneratorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingGeneratorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh Properties")
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh Properties")
	UStaticMeshComponent* WallMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh Properties")
	UStaticMeshComponent* WindowMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh Properties")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh Properties")
	UStaticMeshComponent* RoofMesh;

	UFUNCTION(Category = "World Generation Functions")
	void SetRoomsPerFloor();

	UFUNCTION(Category = "World Generation Functions")
	void AddDoorsToFloor();

	UFUNCTION(Category = "World Generation Functions")
	void AddWindowsToFloor();

	UFUNCTION(Category = "World Generation Functions")
	void AddRoofToLastFloor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Construction Parameters")
	float floors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Construction Parameters")
	float generatedFloors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout Constraints")
	float floorWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout Constraints")
	float floorHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout Constraints")
	int minRooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout Constraints")
	int maxRooms;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "World Generation")
	void GenerateFloor();


};
