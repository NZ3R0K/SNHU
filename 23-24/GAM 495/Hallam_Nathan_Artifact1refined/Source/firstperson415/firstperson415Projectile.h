// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "firstperson415Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class Afirstperson415Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	//Mesh for the ball (sphere)
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ballMesh;

	//Material used for the splat effect
	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	//Randomly generated color used for the splat effect and the ball mesh color
	UPROPERTY()
	FLinearColor randColor;

	//Reference material used for generating the dynamic material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

	//Dynamic material that has color applied to it
	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	//Particle System
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* colorP;


public:
	Afirstperson415Projectile();

protected:
	virtual void BeginPlay();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};