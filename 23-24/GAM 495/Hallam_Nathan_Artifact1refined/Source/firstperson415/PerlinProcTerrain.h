// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class FIRSTPERSON415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	//Procedural generation area X coordinate
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	//Procedural generation area Y coordinate
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	//Multiplier for Height
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
	float ZMultiplier = 1.0f;

	//Intensity of noise
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	float NoiseScale = 1.0f;

	//Multiplied with X and Y coordinate
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0;

	//"resolution" of texture
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0;

	//Radius of hole created by projectile impact
	UPROPERTY(EditAnywhere)
	float radius;

	//Depth of hole created by projecitle impact
	UPROPERTY(EditAnywhere)
	FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Landscape Material
	UPROPERTY(EditAnywhere)
	UMaterialInstance* Mat;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Verticies;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	void CreateVerticies();
	void CreateTriangles();
};
