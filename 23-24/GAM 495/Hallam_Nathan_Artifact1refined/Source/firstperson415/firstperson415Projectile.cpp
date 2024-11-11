// Copyright Epic Games, Inc. All Rights Reserved.

#include "firstperson415Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PerlinProcTerrain.h"


Afirstperson415Projectile::Afirstperson415Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &Afirstperson415Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Add ball mesh to the object
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");

	// Set as root component
	RootComponent = CollisionComp;

	//Make mesh a child of the collision component
	ballMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void Afirstperson415Projectile::BeginPlay()
{
	Super::BeginPlay();
	//Generate random color
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), 1.0f);

	//Create dynamic material
	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);

	//Set the material of the mesh
	ballMesh->SetMaterial(0, dmiMat);

	//Set the color of the material
	dmiMat->SetVectorParameterValue("ProjColor", randColor);
}



void Afirstperson415Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	//If another actor is hit
	if (OtherActor != nullptr)
	{
		if (colorP) 
		{
			//Create new particle system instance at hit location
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(-20.0f, 0.0f, 0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, true);
			//Set particle color
			particleComp->SetNiagaraVariableLinearColor("RandColor", randColor);
			//destroy balls mesh
			ballMesh->DestroyComponent();
			//Set collision profile to no collision so projectile will no longer collide
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
		}

		//Choose frame from sprite sheet for splat effect
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f);

		//Spawn decal at position
		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.0f, 40.0f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
		//Create dynamic material instance
		auto MatInstance = Decal->CreateDynamicMaterialInstance();

		//Set values for dynamic material
		MatInstance->SetVectorParameterValue("Color", randColor);
		MatInstance->SetScalarParameterValue("Frame", frameNum);
	
		//Cast other actor to procedural terrain
		APerlinProcTerrain* procTerrain = Cast<APerlinProcTerrain>(OtherActor);

		//If projectile hit terrain
		if (procTerrain)
		{
			procTerrain->AlterMesh(Hit.ImpactPoint);
		}
	}
}