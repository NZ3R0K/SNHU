// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");	
	ProcMesh->SetupAttachment(GetRootComponent());
	//RootComponent = ProcMesh;
}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();
	
	CreateVerticies();
	CreateTriangles();

	//Create mesh using mesh data given
	ProcMesh->CreateMeshSection(sectionID, Verticies, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);	//Landscape Material Set
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Adjusts the verticies at the given impact point to create a crater
void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	for (int i = 0; i < Verticies.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		//If hit point is in radius
		if (FVector(Verticies[i] - tempVector).Size() < radius)
		{
			Verticies[i] = Verticies[i] - Depth;
			ProcMesh->UpdateMeshSection(sectionID, Verticies, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVerticies()
{
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			//Create vertical Z value based on perlin noise texture
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;
			
			//Used for debug - print to screen Z value
			//GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));
			
			//Add vertex to array multiplied by scale
			Verticies.Add(FVector(X * Scale, Y * Scale, Z));
			//Add UV vertex to array multiplied by UV scale
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	int Vertex = 0;

	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			//Add verticies to draw each triangle
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			Vertex++;
		}

		Vertex++;
	}
}