// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMeshFromStatic::AProcMeshFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");

	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);
}

// Called when the game starts or when spawned
void AProcMeshFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshFromStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProcMeshFromStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

// Called every frame
void AProcMeshFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcMeshFromStatic::GetMeshData()
{
	UStaticMesh* mesh = baseMesh->GetStaticMesh();

	//If mesh is set
	if (mesh)
	{
		//Pull mesh data from static mesh
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Verticies, Triangles, Normals, UV0, Tangents);
		//Update procedural mesh with data from static mesh
		procMesh->UpdateMeshSection(0, Verticies, Normals, UV0, UpVertexColors, Tangents);
		CreateMesh();
	}
}

void AProcMeshFromStatic::CreateMesh()
{
	if (baseMesh)
	{
		//Create procedural mesh with data from static mesh
		procMesh->CreateMeshSection(0, Verticies, Triangles, Normals, UV0, UpVertexColors, Tangents, true);
	}
}

