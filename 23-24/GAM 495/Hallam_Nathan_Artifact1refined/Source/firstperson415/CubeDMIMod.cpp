// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "firstperson415.h"
#include "Kismet/KismetMathLibrary.h"
#include "firstperson415Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();

	//Add callback to overlap event
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

	//If the base material is set
	if (baseMat)
	{
		//Create dynamic material
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	//If the mesh is set
	if (cubeMesh)
	{
		//Set mesh material
		cubeMesh->SetMaterial(0, dmiMat);
	}
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Afirstperson415Character* overlappedActor = Cast<Afirstperson415Character>(OtherActor);

	//If an actor is presently overlapping the collider
	if (overlappedActor)
	{
		//Generate random numbers
		float ranNumx = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumy = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumz = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float randOpacity = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		//Create color
		FLinearColor randColor = FLinearColor(ranNumx, ranNumy, ranNumz, 1.0f);
		
		//If the dynamic material exists
		if (dmiMat)
		{
			//Set values
			dmiMat->SetVectorParameterValue("Color", randColor);
			dmiMat->SetScalarParameterValue("Darkness", ranNumx);
			dmiMat->SetScalarParameterValue("Opacity", randOpacity);

			//Ensure particle system exists
			if (colorP)
			{
				//Create new particle system instance at hit location
				UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, true);
				//Set particle color
				particleComp->SetNiagaraVariableLinearColor("RandColor", randColor);
			}
		}
	}
}

